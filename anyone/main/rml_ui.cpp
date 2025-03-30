#include "rml_ui.h"
#include "base/type.h"
#include <RmlUi/Debugger.h>
#include <RmlUi/Core.h>
#include "embed/default_ttf.h"

const char* demo = R"RAW(
<rml>
<head>
     <link type="text/rcss" href="builtin:///test.rcss"/>
</head>
<body>
    Pasta
</body>
</rml>

)RAW";

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
    MyRenderInterface() : material_(nullptr) { }
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

        MaterialParam params[3] = {
            { .name = "tex",
              .value = { MaterialParamType::TEXTURE, { .tex_unit = 0 } } },
            { .name = "offset",
              .value = { MaterialParamType::VEC2, { .args = offset } } },
            { .name = "canvas_size",
              .value = { MaterialParamType::VEC2, { .args = canvas_size_ } } },
        };

        auto container = (VertexIndiceBuffer*)geometry;
        GET_RENDER_API()->draw(DrawOperation {
            .polygon_mode = PolygonMode::FILL,
            .vertex_buffer = container->vbo,
            .indice_buffer = container->veo,
            .count = container->veo->get_indice_count(),
            .texture = (Texture2D*)texture,
            .textures = nullptr,
            .material = material_,
            .material_params = params,
            .material_params_count = 3,
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

    void set_material(Material* m) { material_ = m; }
    void set_canvas_size(const IntSize& s)
    {
        canvas_size_[0] = s.width;
        canvas_size_[1] = s.height;
    }

private:
    Material* material_;
    float canvas_size_[2];
};

class MyFileInterface : public FileInterface {
public:
    MyFileInterface() { }
    ~MyFileInterface() { }
};

MyRenderInterface* render_impl_ = nullptr;
MySystemInterface* system_impl_ = nullptr;
MyFileInterface* file_impl_ = nullptr;
Material* rml_ui_material_ = nullptr;

void RML_UI::setup()
{
    render_impl_ = new MyRenderInterface;
    system_impl_ = new MySystemInterface;
    file_impl_ = new MyFileInterface;
    rml_ui_material_ = GET_RENDER_API()->create_rml_ui_material();
    render_impl_->set_material(rml_ui_material_);

    Rml::SetRenderInterface(render_impl_);
    Rml::SetSystemInterface(system_impl_);
    Rml::SetFileInterface(file_impl_);
    Rml::Initialise();

    Rml::LoadFontFace({ default_ttf, default_ttf_length },
                      "default",
                      Rml::Style::FontStyle::Normal);
}

void RML_UI::cleanup()
{
    Rml::Shutdown();
    GET_RENDER_API()->destroy_material(rml_ui_material_);
    delete system_impl_;
    delete render_impl_;
    delete file_impl_;
}

RML_UI::RML_UI()
: context_(nullptr)
, document_(nullptr)
// , rml_ui_material_(nullptr)
, canvas_size_ { 0, 0 }
{
    canvas_size_ = GET_CORE()->get_framebuffer_size();
    context_ = Rml::CreateContext(
        "main", Rml::Vector2i(canvas_size_.width, canvas_size_.height));

    // Rml::Debugger::Initialise(context_);
    document_ = context_->LoadDocumentFromMemory(demo);
    if (document_)
        document_->Show();
    auto dpi = GET_CORE()->get_dpi();
    context_->SetDensityIndependentPixelRatio(dpi.vert / 72.0);
    context_->Update();
    NX_ASSERT(document_, "no document");
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

} // namespace anyone
