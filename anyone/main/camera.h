#pragma once

#include "kazmath/kazmath.h"

namespace anyone {

class Camera {
public:
    Camera();

    void set_eye(float x, float y, float z);
    void look_at(float x, float y, float z);
    void set_up(float x, float y, float z);

    const kmMat4* get_view_matrix() const { return &view_matrix_; }
    const kmMat4* get_proj_matrix() const { return &proj_matrix_; }

    void set_aspect(float a);
    void set_fov(float a);

    void set_near_clip(float a);
    void set_far_clip(float a);

    void apply();

    void transform_vp(const kmVec3* in, kmVec4* out) const;
    void transform_vp(const kmVec4* in, kmVec4* out) const;

private:
    kmVec3 eye_;
    kmVec3 look_;
    kmVec3 up_;

    float fov_;
    float aspect_;

    float near_clip_;
    float far_clip_;

    kmMat4 view_matrix_;
    kmMat4 proj_matrix_;
};

} // namespace anyone