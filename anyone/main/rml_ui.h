#pragma once
#include <RmlUi/Core.h>

#include "platform/api/support.h"
#include "main/core.h"

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
    void set_canvas_size(const IntSize& s)
    {
        canvas_size_[0] = s.width;
        canvas_size_[1] = s.height;
    }

private:
    Material* material_;
    float canvas_size_[2];
};

class MySystemInterface : public Rml::SystemInterface {
public:
    MySystemInterface();
    ~MySystemInterface();
};

} // namespace anyone::rml_ui

namespace anyone {

class RML_UI {
public:
    RML_UI();
    ~RML_UI();
    // void update();
    void render();
    void notify_framebuffer_size_changed();

    static void setup();
    static void cleanup();

private:
    static rml_ui::MyRenderInterface* render_impl_;
    static rml_ui::MySystemInterface* system_impl_;
    static Material* rml_ui_material_;

    Rml::Context* context_;
    Rml::ElementDocument* document_;
    IntSize canvas_size_;
};

} // namespace anyone