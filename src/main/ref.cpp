#include "type.h"

namespace anyone {
Ref::Ref() : counter_(1) { }
Ref::~Ref() { }
} // namespace anyone