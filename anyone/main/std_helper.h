#pragma once

#include "base/type.h"

namespace anyone::std_helper {

template <class T>
void remove_value(Vector<T>* container, const T& value)
{
    auto it = std::remove(container->begin(), container->end(), value);
    container->erase(it, container->end());
}

} // namespace anyone::std_helper