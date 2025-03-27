#include "rml_ui.h"
#include <RmlUi/Debugger.h>

namespace anyone {

RML_UI_Context::RML_UI_Context() : context_(nullptr)
{
    Rml::SetRenderInterface(&render_impl_);
    Rml::SetSystemInterface(&system_impl_);
    Rml::Initialise();

    context_ = Rml::CreateContext("main", Rml::Vector2i(800, 600));
    Rml::Debugger::Initialise(context_);
}

RML_UI_Context::~RML_UI_Context()
{
    Rml::RemoveContext("main");
    Rml::Shutdown();
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
    return 0;
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
    return 0;
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
