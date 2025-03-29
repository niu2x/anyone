#include "rml_ui.h"
#include "base/type.h"
#include "main/core.h"
#include <RmlUi/Debugger.h>
#include "embed/default_ttf.h"

const char* demo = R"RAW(

<rml>
<head>
     <link type="text/rcss" href="test.rcss"/>
</head>
<body>
    <p>Hello, niu2x</p>
    <p>Hello, niu2x</p>

</body>
</rml>

)RAW";

// const char* material_source = R"RAW(
// uniform vec2 translation;
// vertex {
//     input 0 vec2 vertex;
//     input 1 vec2 uv;
//     input 2 vec4 color;

//     vec4 main() {

//     }

// }

// fragment {
//     vec4 main() {

//     }
// }

// )RAW";

namespace anyone {

RML_UI_Context::RML_UI_Context()
: context_(nullptr)
, document_(nullptr)
, rml_ui_material_(nullptr)
{
    rml_ui_material_ = GET_RENDER_API()->create_rml_ui_material();
    render_impl_.set_material(rml_ui_material_);

    Rml::SetRenderInterface(&render_impl_);
    Rml::SetSystemInterface(&system_impl_);
    Rml::Initialise();

    context_ = Rml::CreateContext("main", Rml::Vector2i(256, 256));
    // Rml::Debugger::Initialise(context_);
    Rml::LoadFontFace({ default_ttf, default_ttf_length },
                      "default",
                      Rml::Style::FontStyle::Normal);

    document_ = context_->LoadDocumentFromMemory(demo);
    if (document_)
        document_->Show();
    NX_ASSERT(document_, "no document");
}

RML_UI_Context::~RML_UI_Context()
{
    GET_RENDER_API()->destroy_material(rml_ui_material_);

    if (document_) {
        document_->Close();
        document_ = nullptr;
    }
    Rml::RemoveContext("main");
    Rml::Shutdown();
}

void RML_UI_Context::update()
{
    if (context_)
        context_->Update();
}
void RML_UI_Context::render()
{
    if (context_)
        context_->Render();
}

} // namespace anyone

namespace anyone::rml_ui {

MyRenderInterface::MyRenderInterface() : material_(nullptr) { }
MyRenderInterface::~MyRenderInterface() { }

MySystemInterface::MySystemInterface() { }
MySystemInterface::~MySystemInterface() { }

CompiledGeometryHandle
MyRenderInterface::CompileGeometry(Span<const Vertex> vertices,
                                   Span<const int> indices)
{
    struct GPU_Vertex {
        float x, y;
        float u, v;
        uint8_t r, g, b, a;
    };

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
        // LOG("create vbo %d %f %f %f %f %x %x %x %x",
        //     i,
        //     buf[i].x,
        //     buf[i].y,
        //     vertices[i].tex_coord[0],
        //     vertices[i].tex_coord[1],
        //     vertices[i].colour[0],
        //     vertices[i].colour[1],
        //     vertices[i].colour[2],
        //     vertices[i].colour[3]);
    }

    vbo->set_vertex_layout({
        VertexAttr::POSITION_XY,
        VertexAttr::UV,
        VertexAttr::COLOR_BYTE_RGBA,
    });

    // LOG("create vbo %d", vertices.size());

    vbo->apply();
    vbo->free_cpu_buffer();

    IndiceBuffer* veo = GET_RENDER_API()->create_indice_buffer();
    veo->alloc_cpu_buffer(indices.size());
    auto indice_buf = veo->get_cpu_buffer();
    for (int i = 0; i < indices.size(); i++) {
        indice_buf[i] = indices[i];
        // LOG("create veo %d %d", i, indice_buf[i]);
    }
    veo->apply();
    veo->free_cpu_buffer();

    auto container = new VertexIndiceBuffer;
    container->vbo = vbo;
    container->veo = veo;

    // LOG("create veo %d", indices.size());
    return (uintptr_t)container;
}

void MyRenderInterface::RenderGeometry(CompiledGeometryHandle geometry,
                                       Vector2f translation,
                                       TextureHandle texture)
{
    float offset[2] = { translation[0], translation[1] };
    MaterialParam params[3] = {
        { .name = "tex",
          .value = { MaterialParamType::TEXTURE, { .tex_unit = 0 } } },
        { .name = "offset",
          .value = { MaterialParamType::VEC2, { .args = offset } } },
        { .name = "tex",
          .value = { MaterialParamType::TEXTURE, { .tex_unit = 0 } } },
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
        .material_params_count = 2,
    });

    // LOG("draw %d %f %f",
    //     container->veo->get_indice_count(),
    //     translation[0],
    //     translation[1]);
}

void MyRenderInterface::ReleaseGeometry(CompiledGeometryHandle geometry)
{
    // LOG("ReleaseGeometry");
    auto container = (VertexIndiceBuffer*)geometry;
    GET_RENDER_API()->destroy_vertex_buffer(container->vbo);
    GET_RENDER_API()->destroy_indice_buffer(container->veo);
    delete container;
}

TextureHandle MyRenderInterface::LoadTexture(Vector2i& texture_dimensions,
                                             const String& source)
{
    // LOG("LoadTexture %s", source.c_str());
    return 0;
}

TextureHandle MyRenderInterface::GenerateTexture(Span<const byte> source,
                                                 Vector2i source_dimensions)
{
    // LOG("GenerateTexture %d %d %d",
    //     source.size(),
    //     source_dimensions[0],
    //     source_dimensions[1]);
    //
    auto tex = GET_RENDER_API()->create_texture_2d();
    tex->alloc_cpu_buffer(source_dimensions[0], source_dimensions[1]);
    memcpy(tex->get_cpu_buffer(), source.data(), source.size());
    tex->apply();
    tex->free_cpu_buffer();
    return (uintptr_t)tex;
}

void MyRenderInterface::ReleaseTexture(TextureHandle texture)
{
    GET_RENDER_API()->destroy_texture_2d((Texture2D*)texture);
}

void MyRenderInterface::EnableScissorRegion(bool enable) { }

void MyRenderInterface::SetScissorRegion(Rectanglei region) { }

}; // namespace anyone::rml_ui
