#pragma once

#include "base/type.h"

namespace anyone {

class Mesh {
public:
    Mesh(const String& name);
    ~Mesh();
    bool load_from_file(const String& name);

private:
    String name_;
};

} // namespace anyone