#include "camera.h"

namespace anyone {

Camera::Camera()
: eye_ { 0, 0, 0 }
, look_ { 0, 0, 0 }
, up_ { 0, 0, 0 }
, fov_(60)
, aspect_(1)
, near_clip_(0.1)
, far_clip_(1000)
{
}

void Camera::set_eye(float x, float y, float z) { eye_ = { x, y, z }; }

void Camera::look_at(float x, float y, float z) { look_ = { x, y, z }; }

void Camera::set_up(float x, float y, float z) { up_ = { x, y, z }; }

kmMat4 Camera::get_view_matrix() const
{
    kmMat4 mat;
    kmMat4LookAt(&mat, &eye_, &look_, &up_);
    return mat;
}

kmMat4 Camera::get_proj_matrix() const
{
    kmMat4 mat;
    kmMat4PerspectiveProjection(&mat, fov_, aspect_, near_clip_, far_clip_);
    return mat;
}

void Camera::set_aspect(float a) { aspect_ = a; }

void Camera::set_fov(float a) { fov_ = a; }

void Camera::set_near_clip(float a) { near_clip_ = a; }

void Camera::set_far_clip(float a) { far_clip_ = a; }

void Camera::transform_vp(const kmVec3* in, kmVec4* out) const
{
    kmVec4 tmp { in->x, in->y, in->z, 1 };
    transform_vp(&tmp, out);
}

void Camera::transform_vp(const kmVec4* in, kmVec4* out) const
{
    auto view = get_view_matrix();
    auto proj = get_proj_matrix();
    kmVec4 tmp;
    kmVec4Transform(&tmp, in, &view);
    kmVec4Transform(out, &tmp, &proj);
}

} // namespace anyone
