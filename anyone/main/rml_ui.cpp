#include "rml_ui.h"
#include "base/type.h"
#include "main/core.h"
#include <RmlUi/Debugger.h>
#include "embed/default_ttf.h"

const char* demo = R"RAW(

<rml>
<head>
    <title>Hello world</title>
</head>
<body>
    <h1>RmlUi</h1>
    <p>Hello <span id="world">world</span>!</p>
</body>
</rml>

)RAW";

namespace anyone {

RML_UI_Context::RML_UI_Context() : context_(nullptr), document_(nullptr)
{
    Rml::SetRenderInterface(&render_impl_);
    Rml::SetSystemInterface(&system_impl_);
    Rml::Initialise();

    context_ = Rml::CreateContext("main", Rml::Vector2i(800, 600));
    Rml::Debugger::Initialise(context_);
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

MyRenderInterface::MyRenderInterface() { }
MyRenderInterface::~MyRenderInterface() { }

MySystemInterface::MySystemInterface() { }
MySystemInterface::~MySystemInterface() { }

CompiledGeometryHandle
MyRenderInterface::CompileGeometry(Span<const Vertex> vertices,
                                   Span<const int> indices)
{
    return 1;
}

void MyRenderInterface::RenderGeometry(CompiledGeometryHandle geometry,
                                       Vector2f translation,
                                       TextureHandle texture)
{
}

void MyRenderInterface::ReleaseGeometry(CompiledGeometryHandle geometry) { }

TextureHandle MyRenderInterface::LoadTexture(Vector2i& texture_dimensions,
                                             const String& source)
{
    return 1;
}

TextureHandle MyRenderInterface::GenerateTexture(Span<const byte> source,
                                                 Vector2i source_dimensions)
{
    return 0;
}

void MyRenderInterface::ReleaseTexture(TextureHandle texture) { }

void MyRenderInterface::EnableScissorRegion(bool enable) { }

void MyRenderInterface::SetScissorRegion(Rectanglei region) { }

}; // namespace anyone::rml_ui
