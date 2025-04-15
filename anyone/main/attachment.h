#pragma once

#include "base/type.h"
#include "platform/api/support.h"
#include "kazmath/kazmath.h"

namespace anyone {

class Camera;

class Attachment {
public:
    Attachment();
    virtual ~Attachment() = 0;
};

class Renderable : public Attachment {
public:
    virtual void draw(const Camera* camera,
                      const kmMat4* transform,
                      CubeMap* sky_box)
        = 0;
};

} // namespace anyone