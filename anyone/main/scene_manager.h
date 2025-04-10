#pragma once

#include "base/color.h"
#include "platform/api/support.h"

namespace anyone {

class Camera;
class SceneNode;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void render(const Camera* camera);
    SceneNode* get_root_node() const { return root_; }
    const Color& get_sky_color() const { return sky_color_; };

private:
    SceneNode* root_;
    Color ambient_color_;
    Color sky_color_;

    VertexBuffer* axis_vbo_;
    IndiceBuffer* axis_veo_;

    void draw_axis(const Camera* camera);
};

} // namespace anyone