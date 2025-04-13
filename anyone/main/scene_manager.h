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

    void set_sky_box(CubeMap* c);

private:
    SceneNode* root_;
    Color ambient_color_;
    Color sky_color_;

    VertexBuffer* axis_vbo_;
    IndiceBuffer* axis_veo_;

    VertexBuffer* sky_box_vbo_;
    IndiceBuffer* sky_box_veo_;
    Program* sky_box_program_;
    CubeMap* sky_box_;

    void draw_axis(const Camera* camera);
    void draw_sky_box(const Camera* camera);

    void init_axis();
    void init_sky_box();
};

} // namespace anyone