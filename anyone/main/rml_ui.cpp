#include "rml_ui.h"
#include "base/type.h"
#include <RmlUi/Debugger.h>
#include "embed/SpaceMono_Regular.h"
#include "main/core.h"

// const char* demo = R"RAW(
// <rml>
// <head>
//      <link type="text/rcss" href="builtin:///style/basic.rcss"/>
// </head>
// <body>
//     Pasta
// </body>
// </rml>

// )RAW";

namespace anyone {

using namespace Rml;

class MySystemInterface : public Rml::SystemInterface {
public:
    MySystemInterface() { }
    ~MySystemInterface() { }
};

struct GPU_Vertex {
    float x, y;
    float u, v;
    uint8_t r, g, b, a;
};

class MyRenderInterface : public Rml::RenderInterface {
public:
    MyRenderInterface() : program_(nullptr) { }
    ~MyRenderInterface() { }
    CompiledGeometryHandle CompileGeometry(Span<const Vertex> vertices,
                                           Span<const int> indices) override
    {

        auto vbo = GET_RENDER_API()->create_vertex_buffer();
        vbo->alloc_cpu_buffer(sizeof(GPU_Vertex) * vertices.size());
        auto buf = (GPU_Vertex*)vbo->get_cpu_buffer();
        for (int i = 0; i < vertices.size(); i++) {
            buf[i].x = vertices[i].position[0];
            buf[i].y = vertices[i].position[1];
            buf[i].r = vertices[i].colour[0];
            buf[i].g = vertices[i].colour[1];
            buf[i].b = vertices[i].colour[2];
            buf[i].a = vertices[i].colour[3];
            buf[i].u = vertices[i].tex_coord[0];
            buf[i].v = vertices[i].tex_coord[1];
        }

        vbo->set_vertex_layout({
            VertexAttr::POSITION_XY,
            VertexAttr::UV,
            VertexAttr::COLOR_BYTE_RGBA,
        });

        vbo->apply();
        vbo->free_cpu_buffer();

        IndiceBuffer* veo = GET_RENDER_API()->create_indice_buffer();
        veo->alloc_cpu_buffer(indices.size());
        auto indice_buf = veo->get_cpu_buffer();
        for (int i = 0; i < indices.size(); i++) {
            indice_buf[i] = indices[i];
        }
        veo->apply();
        veo->free_cpu_buffer();

        auto container = new VertexIndiceBuffer;
        container->vbo = vbo;
        container->veo = veo;

        return (uintptr_t)container;
    }

    void RenderGeometry(CompiledGeometryHandle geometry,
                        Vector2f translation,
                        TextureHandle texture) override
    {

        float offset[2] = { translation[0], translation[1] };

        ProgramParam params[3] = {
            { .name = "tex",
              .value = { ProgramParamType::TEXTURE, { .tex_unit = 0 } } },
            { .name = "offset",
              .value = { ProgramParamType::VEC2, { .args = offset } } },
            { .name = "canvas_size",
              .value = { ProgramParamType::VEC2, { .args = canvas_size_ } } },
        };

        auto container = (VertexIndiceBuffer*)geometry;
        GET_RENDER_API()->draw(DrawOperation {
            .polygon_mode = PolygonMode::FILL,
            .vertex_buffer = container->vbo,
            .indice_buffer = container->veo,
            .count = container->veo->get_indice_count(),
            .texture = (Texture2D*)texture,
            .textures = nullptr,
            .program = program_,
            .program_params = params,
            .program_params_count = 3,
        });
    }

    void ReleaseGeometry(CompiledGeometryHandle geometry) override
    {
        auto container = (VertexIndiceBuffer*)geometry;
        GET_RENDER_API()->destroy_vertex_buffer(container->vbo);
        GET_RENDER_API()->destroy_indice_buffer(container->veo);
        delete container;
    }

    TextureHandle LoadTexture(Vector2i& texture_dimensions,
                              const String& source) override
    {
        return 0;
    }

    TextureHandle GenerateTexture(Span<const byte> source,
                                  Vector2i source_dimensions) override
    {

        auto tex = GET_RENDER_API()->create_texture_2d();
        tex->alloc_cpu_buffer(source_dimensions[0], source_dimensions[1]);
        memcpy(tex->get_cpu_buffer(), source.data(), source.size());
        tex->apply();
        tex->free_cpu_buffer();
        return (uintptr_t)tex;
    }

    void ReleaseTexture(TextureHandle texture) override
    {
        GET_RENDER_API()->destroy_texture_2d((Texture2D*)texture);
    }

    void EnableScissorRegion(bool enable) override { }
    void SetScissorRegion(Rectanglei region) override { }

    void set_program(Program* m) { program_ = m; }
    void set_canvas_size(const IntSize& s)
    {
        canvas_size_[0] = s.width;
        canvas_size_[1] = s.height;
    }

private:
    Program* program_;
    float canvas_size_[2];
};

class FileAdapter {
public:
    explicit FileAdapter(nx::UniquePtr<Read> reader) : position_(0)
    {
        auto ret = reader->read_all();

        if (std::holds_alternative<IO_Error>(ret)) {
            return;
        }

        buffer_ = std::get<ByteBuffer>(std::move(ret));
    }
    ~FileAdapter() { }

    size_t read(void* buffer, size_t size)
    {
        size = std::min(size, buffer_.size() - position_);

        memcpy(buffer, buffer_.data() + position_, size);
        position_ += size;

        return size;
    }

    bool seek(long offset, int origin)
    {
        if (origin == SEEK_SET) {
            position_ = offset;
            return true;
        } else if (origin == SEEK_CUR) {
            position_ += offset;
            return true;
        } else if (origin == SEEK_END) {
            position_ = buffer_.size() + offset;
            return true;
        } else {
            return false;
        }
    }
    size_t tell() const { return position_; }

private:
    ByteBuffer buffer_;
    off_t position_;
};

class MyFileInterface : public FileInterface {
public:
    MyFileInterface() { }
    ~MyFileInterface() { }

    /// Opens a file.
    /// @param path The path to the file to open.
    /// @return A valid file handle, or nullptr on failure
    FileHandle Open(const String& path) override
    {
        if (strncmp("builtin://", path.c_str(), 10) == 0) {
            auto reader = GET_CORE()->read_builtin_file(path.substr(10));
            if (reader) {
                auto adapter = new FileAdapter(std::move(reader));
                return (uintptr_t)adapter;
            }
        }
        return 0;
    }
    /// Closes a previously opened file.
    /// @param file The file handle previously opened through Open().
    void Close(FileHandle file) override
    {
        auto adapter = (FileAdapter*)file;
        if (adapter)
            delete adapter;
    }

    /// Reads data from a previously opened file.
    /// @param buffer The buffer to be read into.
    /// @param size The number of bytes to read into the buffer.
    /// @param file The handle of the file.
    /// @return The total number of bytes read into the buffer.
    size_t Read(void* buffer, size_t size, FileHandle file) override
    {
        auto adapter = (FileAdapter*)file;
        if (adapter) {
            return adapter->read(buffer, size);
        }
        return 0;
    }
    /// Seeks to a point in a previously opened file.
    /// @param file The handle of the file to seek.
    /// @param offset The number of bytes to seek.
    /// @param origin One of either SEEK_SET (seek from the beginning of the
    /// file), SEEK_END (seek from the end of the file) or SEEK_CUR (seek from
    /// the current file position).
    /// @return True if the operation completed successfully, false otherwise.
    bool Seek(FileHandle file, long offset, int origin) override
    {
        auto adapter = (FileAdapter*)file;
        if (adapter) {
            return adapter->seek(offset, origin);
        }
        return false;
    }
    /// Returns the current position of the file pointer.
    /// @param file The handle of the file to be queried.
    /// @return The number of bytes from the origin of the file.
    size_t Tell(FileHandle file) override
    {
        auto adapter = (FileAdapter*)file;
        if (adapter) {
            return adapter->tell();
        }
        return 0;
    }
};

MyRenderInterface* render_impl_ = nullptr;
MySystemInterface* system_impl_ = nullptr;
MyFileInterface* file_impl_ = nullptr;
Program* rml_ui_program_ = nullptr;

void RML_UI::setup()
{
    render_impl_ = new MyRenderInterface;
    system_impl_ = new MySystemInterface;
    file_impl_ = new MyFileInterface;
    rml_ui_program_ = GET_RENDER_API()->create_rml_ui_program();
    render_impl_->set_program(rml_ui_program_);

    Rml::SetRenderInterface(render_impl_);
    Rml::SetSystemInterface(system_impl_);
    Rml::SetFileInterface(file_impl_);
    Rml::Initialise();

    Rml::LoadFontFace({ SpaceMono_Regular, SpaceMono_Regular_length },
                      "SpaceMono",
                      Rml::Style::FontStyle::Normal);
}

void RML_UI::cleanup()
{
    Rml::Shutdown();
    GET_RENDER_API()->destroy_program(rml_ui_program_);
    delete system_impl_;
    delete render_impl_;
    // delete file_impl_;
}

RML_UI::RML_UI()
: context_(nullptr)
, document_(nullptr)
// , rml_ui_program_(nullptr)
, canvas_size_ { 0, 0 }
{
    canvas_size_ = GET_CORE()->get_framebuffer_size();
    context_ = Rml::CreateContext(
        "main", Rml::Vector2i(canvas_size_.width, canvas_size_.height));

    // Rml::Debugger::Initialise(context_);
    // document_ = context_->LoadDocumentFromMemory(demo);
    // if (document_)
    // document_->Show();
    auto dpi = GET_CORE()->get_dpi();
    context_->SetDensityIndependentPixelRatio(dpi.vert / 72.0);
    context_->Update();
}

void RML_UI::load_document(const String& uri)
{
    NX_ASSERT(!document_, "already exist document");
    document_ = context_->LoadDocument(uri);
    if (document_)
        document_->Show();
}

RML_UI::~RML_UI()
{
    if (document_) {
        document_->Close();
        document_ = nullptr;
    }
    Rml::RemoveContext("main");
}

void RML_UI::notify_framebuffer_size_changed()
{
    canvas_size_ = GET_CORE()->get_framebuffer_size();

    context_->SetDimensions(
        Rml::Vector2i(canvas_size_.width, canvas_size_.height));

    auto dpi = GET_CORE()->get_dpi();
    context_->SetDensityIndependentPixelRatio(dpi.vert / 72.0);

    context_->Update();
}

void RML_UI::render()
{
    render_impl_->set_canvas_size(canvas_size_);
    context_->Render();
}

void RML_UI::update() {
    context_->Update();
}

} // namespace anyone
