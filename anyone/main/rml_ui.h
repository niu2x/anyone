#pragma once
#include <RmlUi/Core.h>

#include "platform/api/support.h"

namespace anyone::rml_ui {

using namespace Rml;

class MyRenderInterface : public Rml::RenderInterface {
public:
    MyRenderInterface();
    ~MyRenderInterface();
    CompiledGeometryHandle CompileGeometry(Span<const Vertex> vertices,
                                           Span<const int> indices) override;

    void RenderGeometry(CompiledGeometryHandle geometry,
                        Vector2f translation,
                        TextureHandle texture) override;

    void ReleaseGeometry(CompiledGeometryHandle geometry) override;
    TextureHandle LoadTexture(Vector2i& texture_dimensions,
                              const String& source) override;
    TextureHandle GenerateTexture(Span<const byte> source,
                                  Vector2i source_dimensions) override;

    void ReleaseTexture(TextureHandle texture) override;
    void EnableScissorRegion(bool enable) override;
    void SetScissorRegion(Rectanglei region) override;

    void set_material(Material* m) { material_ = m; }

private:
    Material* material_;
};

class MySystemInterface : public Rml::SystemInterface {
public:
    MySystemInterface();
    ~MySystemInterface();
};

} // namespace anyone::rml_ui

namespace anyone {

class RML_UI_Context {
public:
    RML_UI_Context();
    ~RML_UI_Context();

    void update();
    void render();

private:
    rml_ui::MyRenderInterface render_impl_;
    rml_ui::MySystemInterface system_impl_;
    Rml::Context* context_;
    Rml::ElementDocument* document_;
    Material* rml_ui_material_;
};

} // namespace anyone