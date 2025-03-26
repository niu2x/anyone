#include "type.h"

namespace anyone {

Ref::Ref() : counter_(1)
{
    object_counter_++;
    alive_objects_.insert(this);
}
Ref::~Ref()
{
    object_counter_--;
    alive_objects_.erase(this);
}

uint64_t Ref::object_counter_ = 0;
std::unordered_set<Ref*> Ref::alive_objects_;

void Ref::dump_alive_objects()
{
    for (auto& x : alive_objects_) {
        printf("alive ref object: %s\n", x->get_type());
    }
}

} // namespace anyone