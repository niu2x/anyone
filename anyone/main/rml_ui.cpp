#include "rml_ui.h"

namespace anyone {

RML_UI::RML_UI()
{
    Rml::SetRenderInterface(&render_impl_);
    Rml::SetSystemInterface(&system_impl_);
}

RML_UI::~RML_UI() { }

} // namespace anyone