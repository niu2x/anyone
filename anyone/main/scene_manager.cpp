#include "model.h"
#include "core.h"
#include "scene_manager.h"
#include "scene_node.h"

namespace anyone {

SceneManager::SceneManager()
: root_(nullptr)
, ambient_color_(Color::DARK_SLATE_GRAY)
, sky_color_(Color::DARK_SLATE_GRAY)
, axis_vbo_(nullptr)
, axis_veo_(nullptr)
, sky_box_(nullptr)
, sky_box_vbo_(nullptr)
, sky_box_veo_(nullptr)
, sky_box_program_(nullptr)
{
    root_ = new SceneNode("/");
    // root_->apply_transform(nullptr);
    init_axis();
    init_sky_box();
}

void SceneManager::init_axis()
{

    axis_vbo_ = GET_RENDER_API()->create_vertex_buffer();
    axis_veo_ = GET_RENDER_API()->create_indice_buffer();

    struct GPU_Vertex {
        float x, y, z;
    };

    axis_vbo_->alloc_cpu_buffer(4 * sizeof(GPU_Vertex));
    {
        auto buf = (GPU_Vertex*)axis_vbo_->get_cpu_buffer();
        buf[0].x = 0;
        buf[0].y = 0;
        buf[0].z = 0;

        buf[1].x = 10000;
        buf[1].y = 0;
        buf[1].z = 0;

        buf[2].x = 0;
        buf[2].y = 10000;
        buf[2].z = 0;

        buf[3].x = 0;
        buf[3].y = 0;
        buf[3].z = 10000;
    }

    axis_vbo_->apply();
    axis_vbo_->free_cpu_buffer();
    axis_vbo_->set_vertex_layout({ VertexAttr::POSITION_XYZ });

    axis_veo_->alloc_cpu_buffer(6);
    {
        auto buf = axis_veo_->get_cpu_buffer();
        buf[0] = 0;
        buf[1] = 1;

        buf[2] = 0;
        buf[3] = 2;

        buf[4] = 0;
        buf[5] = 3;
    }

    axis_veo_->apply();
    axis_veo_->free_cpu_buffer();
}

void SceneManager::init_sky_box()
{

    sky_box_vbo_ = GET_RENDER_API()->create_vertex_buffer();
    sky_box_veo_ = GET_RENDER_API()->create_indice_buffer();

    struct GPU_Vertex {
        float x, y, z;
    };

    sky_box_vbo_->alloc_cpu_buffer(8 * sizeof(GPU_Vertex));
    {
        auto buf = (GPU_Vertex*)sky_box_vbo_->get_cpu_buffer();
        buf[0].x = -1;
        buf[0].y = -1;
        buf[0].z = -1;

        buf[1].x = -1;
        buf[1].y = 1;
        buf[1].z = -1;

        buf[2].x = 1;
        buf[2].y = 1;
        buf[2].z = -1;

        buf[3].x = 1;
        buf[3].y = -1;
        buf[3].z = -1;

        buf[4].x = -1;
        buf[4].y = -1;
        buf[4].z = 1;

        buf[5].x = -1;
        buf[5].y = 1;
        buf[5].z = 1;

        buf[6].x = 1;
        buf[6].y = 1;
        buf[6].z = 1;

        buf[7].x = 1;
        buf[7].y = -1;
        buf[7].z = 1;
    }

    sky_box_vbo_->apply();
    sky_box_vbo_->free_cpu_buffer();
    sky_box_vbo_->set_vertex_layout({ VertexAttr::POSITION_XYZ });

    sky_box_veo_->alloc_cpu_buffer(36);
    {
        auto buf = sky_box_veo_->get_cpu_buffer();
        int i = 0;

        buf[i++] = 0;
        buf[i++] = 2;
        buf[i++] = 1;
        buf[i++] = 0;
        buf[i++] = 3;
        buf[i++] = 2;

        buf[i++] = 5;
        buf[i++] = 6;
        buf[i++] = 4;
        buf[i++] = 6;
        buf[i++] = 7;
        buf[i++] = 4;

        buf[i++] = 1;
        buf[i++] = 6;
        buf[i++] = 5;
        buf[i++] = 1;
        buf[i++] = 2;
        buf[i++] = 6;

        buf[i++] = 7;
        buf[i++] = 0;
        buf[i++] = 4;
        buf[i++] = 7;
        buf[i++] = 3;
        buf[i++] = 0;

        buf[i++] = 2;
        buf[i++] = 7;
        buf[i++] = 6;
        buf[i++] = 2;
        buf[i++] = 3;
        buf[i++] = 7;

        buf[i++] = 1;
        buf[i++] = 5;
        buf[i++] = 4;
        buf[i++] = 1;
        buf[i++] = 4;
        buf[i++] = 0;
    }

    sky_box_veo_->apply();
    sky_box_veo_->free_cpu_buffer();

    sky_box_program_ = GET_RENDER_API()->create_sky_box_program();
}

void SceneManager::set_sky_box(CubeMap* c)
{
    if (sky_box_) {
        GET_RENDER_API()->destroy_cube_map(sky_box_);
    }
    sky_box_ = c;
}

SceneManager::~SceneManager()
{
    if (sky_box_) {
        GET_RENDER_API()->destroy_cube_map(sky_box_);
    }

    GET_RENDER_API()->destroy_indice_buffer(sky_box_veo_);
    GET_RENDER_API()->destroy_vertex_buffer(sky_box_vbo_);
    GET_RENDER_API()->destroy_program(sky_box_program_);

    GET_RENDER_API()->destroy_indice_buffer(axis_veo_);
    GET_RENDER_API()->destroy_vertex_buffer(axis_vbo_);

    if (root_)
        delete root_;
}
void SceneManager::render(const Camera* camera)
{
    root_->apply_transform_recursive(nullptr, false);

    // draw sky box

    draw_sky_box(camera);

    root_->render(camera, sky_box_);
    draw_axis(camera);
}

void SceneManager::draw_sky_box(const Camera* camera)
{
    if (sky_box_) {
        GET_RENDER_API()->set_depth_test(true);

        sky_box_->bind(0);
        sky_box_program_->use();
        sky_box_program_->set_param_texture("tex", 0);

        auto view = camera->get_view_matrix();
        auto proj = camera->get_proj_matrix();

        sky_box_program_->set_param_mat4("view", view->mat);
        sky_box_program_->set_param_mat4("proj", proj->mat);

        auto eye_pos = camera->get_eye();
        sky_box_program_->set_param_vec3("eye_pos", eye_pos->x, eye_pos->y, eye_pos->z);


        GET_RENDER_API()->draw(DrawOperation {
            .primitive = PrimitiveType::TRIANGLE,
            .polygon_mode = PolygonMode::FILL,
            .vertex_buffer = sky_box_vbo_,
            .indice_buffer = sky_box_veo_,
            .count = sky_box_veo_->get_indice_count(),
        });
    }
}

void SceneManager::draw_axis(const Camera* camera)
{
    auto view = camera->get_view_matrix();
    auto proj = camera->get_proj_matrix();
    kmMat4 model_matrix;
    kmMat4Identity(&model_matrix);

    GET_RENDER_API()->set_depth_test(true);
    GET_RENDER_API()->set_blend_type(BlendType::NORMAL);
    auto program = Model::get_program();
    program->use();

    float ambient[] = { 1, 1, 1 };
    float light_direction[] = { 1 / 3.0, 1 / 3.0, 1 / 3.0 };
    program->set_param_vec3("ambient", ambient);
    program->set_param_vec3("light_direction", light_direction);
    program->set_param_mat4("view", view->mat);
    program->set_param_mat4("model", model_matrix.mat);
    program->set_param_mat4("proj", proj->mat);

    GET_RENDER_API()->draw(DrawOperation {
        .primitive = PrimitiveType::LINE,
        .polygon_mode = PolygonMode::FILL,
        .vertex_buffer = axis_vbo_,
        .indice_buffer = axis_veo_,
        .count = axis_veo_->get_indice_count(),
    });
}

} // namespace anyone