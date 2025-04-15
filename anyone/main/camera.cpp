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
    kmVec4 tmp;
    kmVec4Transform(&tmp, in, &view_matrix_);
    kmVec4Transform(out, &tmp, &proj_matrix_);
}

void Camera::apply()
{
    kmMat4PerspectiveProjection(
        &proj_matrix_, fov_, aspect_, near_clip_, far_clip_);
    kmMat4LookAt(&view_matrix_, &eye_, &look_, &up_);
}

void Camera::translate(float x, float y, float z)
{
    kmVec3 translation = { x, y, z };
    kmVec3Add(&eye_, &eye_, &translation);
    kmVec3Add(&look_, &look_, &translation);
}

void Camera::rotate(float radians, float x, float y, float z)
{
    kmVec3 axis { x, y, z };
    // 绕相机自身的轴旋转
    kmMat4 rotation;
    kmMat4RotationAxisAngle(&rotation, &axis, radians);

    // 旋转相机的朝向向量
    kmVec3 forward;
    kmVec3Subtract(&forward, &look_, &eye_);
    kmVec3Transform(&forward, &forward, &rotation);
    kmVec3Add(&look_, &eye_, &forward);

    // 旋转相机的上向量
    kmVec3Transform(&up_, &up_, &rotation);
}

void Camera::zoom(float factor)
{
    fov_ *= factor;
    if (fov_ < 1.0f)
        fov_ = 1.0f;
    if (fov_ > 179.0f)
        fov_ = 179.0f;
}

void Camera::orbit(float radians, float x, float y, float z)
{
    kmVec3 axis { x, y, z };
    kmMat4 rotation;
    kmMat4RotationAxisAngle(&rotation, &axis, radians);

    // 计算相机到目标点的向量
    kmVec3 offset;
    kmVec3Subtract(&offset, &eye_, &look_);

    // 旋转偏移向量
    kmVec3Transform(&offset, &offset, &rotation);

    // 更新相机位置
    kmVec3Add(&eye_, &look_, &offset);

    // 旋转相机的上向量
    kmVec3Transform(&up_, &up_, &rotation);
}

} // namespace anyone
