#include "type.h"

namespace anyone {

Ref::Ref() : counter_(1) { object_counter_++; }
Ref::~Ref() { object_counter_--; }

uint64_t Ref::object_counter_ = 0;

} // namespace anyone