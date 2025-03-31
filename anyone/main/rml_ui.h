#pragma once

#include "platform/api/support.h"
#include "main/core.h"

namespace Rml {
class Context;
class ElementDocument;
}; // namespace Rml

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

    void load_document(const String& uri);

private:
    Rml::Context* context_;
    Rml::ElementDocument* document_;
    IntSize canvas_size_;
};

} // namespace anyone