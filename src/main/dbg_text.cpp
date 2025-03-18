#include "dbg_text.h"

namespace anyone {

const char* dbg_text_vertex_source = R"(
    #version 330 core

    layout(location = 0) in vec2 position;
    layout(location = 1) in vec2 uv;

    uniform vec2 framebuffer_size;

    out vec2 v_uv;

    void main() {
        vec2 p = position;
        p.xy /= framebuffer_size;
        p.xy *= 2;
        p.xy -= vec2(1.0, 1.0);
        p.y = -p.y;
        gl_Position = vec4(p.x, p.y, 0.0,  1.0);
        v_uv = uv;
    }

)";

const char* dbg_text_fragment_source = R"(
    #version 330 core

    uniform sampler2D tex;
    uniform vec4 font_color;

    in vec2 v_uv;
    out vec4 color;
    void main() {
        color = font_color * texture(tex, v_uv).r;
    }
)";

void DebugText::clear()
{
    memset(screens_.data(), 0, screens_.size());
    dirty_ = true;
}

DebugText::DebugText(Font* font)
: font_(font)
, dirty_(true)
, vbo_(nullptr)
, vertex_count_(0)
, texture_(nullptr)
{

    screens_.resize(get_cell_count());
    memset(screens_.data(), 0, screens_.size());
    program_ = create_gl_program(dbg_text_vertex_source,
                                 dbg_text_fragment_source);

    GET_CORE()->add_framebuffer_size_listener(this);
}

int DebugText::get_cell_count() const
{
    auto size = GET_CORE()->get_framebuffer_size();
    return (size.width / get_font_width()) * (size.height / get_font_height());
}

int DebugText::get_font_width() const
{
    auto font_size = font_->get_font_pixel_size();
    return font_size * 0.6;
}

int DebugText::get_font_height() const
{
    auto font_size = font_->get_font_pixel_size();
    return font_size;
}

DebugText::~DebugText()
{
    GET_CORE()->remove_framebuffer_size_listener(this);

    program_->release();

    if (vbo_)
        vbo_->release();
}

void DebugText::on_framebuffer_size_changed()
{
    screens_.resize(get_cell_count());
    memset(screens_.data(), 0, screens_.size());
    dirty_ = true;
}

struct Vertex {
    float x, y;
    float u, v;
};

void DebugText::printf(int x, int y, const char* msg)
{
    auto size = GET_CORE()->get_framebuffer_size();
    int cell_width = (size.width / get_font_width());

    for (int i = 0; i < strlen(msg); i++) {
        if (x + i >= 0 && x + i < cell_width) {
            screens_[x + i + y * cell_width] = msg[i];
        }
    }

    dirty_ = true;
}

void DebugText::render()
{
    auto size = GET_CORE()->get_framebuffer_size();

    if (dirty_) {
        auto font_width = get_font_width();
        auto font_height = get_font_height();

        dirty_ = false;

        if (vbo_) {
            vbo_->release();
            vbo_ = nullptr;
        }

        int chars_counter = 0;
        GL_Texture2D* texture;

        for (int i = 0; i < screens_.size(); i++) {
            char c = screens_[i];
            if (c) {
                auto x = i % (size.width / font_width);
                auto y = i / (size.width / font_width);
                chars_counter++;
            }
        }

        if (chars_counter > 0) {
            vbo_ = new GL_VertexBuffer(sizeof(Vertex) * 6 * chars_counter);
            vbo_->set_vertex_layout(
                { VertexAttr::POSITION_XY, VertexAttr::UV });
            vbo_->alloc_cpu_buffer();

            Vertex* vertexs = (Vertex*)vbo_->get_cpu_buffer();
            int vertex_index = 0;

            for (int i = 0; i < screens_.size(); i++) {
                char c = screens_[i];
                if (c) {
                    auto char_info = font_->lookup_char(c);
                    if (char_info) {
                        texture = char_info->texture;

                        auto cell_x = i % (size.width / font_width);
                        auto cell_y = i / (size.width / font_width);

                        vertexs[vertex_index++] = {
                            .x = cell_x * font_width + char_info->bitmap_left,
                            .y = cell_y * font_height + font_height * 0.666
                                 - char_info->bitmap_top,
                            .u = ((float)char_info->left)
                                 / texture->get_width(),
                            .v = ((float)char_info->top)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * font_width + char_info->bitmap_left,
                            .y = cell_y * font_height + char_info->height
                                 + font_height * 0.666 - char_info->bitmap_top,
                            .u = ((float)char_info->left)
                                 / texture->get_width(),
                            .v = ((float)char_info->top + char_info->height)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * font_width + char_info->width
                                 + char_info->bitmap_left,
                            .y = cell_y * font_height + char_info->height
                                 + font_height * 0.666 - char_info->bitmap_top,
                            .u = ((float)char_info->left + char_info->width)
                                 / texture->get_width(),
                            .v = ((float)char_info->top + char_info->height)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index] = vertexs[vertex_index - 3];
                        vertex_index++;

                        vertexs[vertex_index] = vertexs[vertex_index - 2];
                        vertex_index++;

                        vertexs[vertex_index++] = {
                            .x = cell_x * font_width + char_info->width
                                 + char_info->bitmap_left,
                            .y = cell_y * font_height + font_height * 0.666
                                 - char_info->bitmap_top,
                            .u = ((float)char_info->left + char_info->width)
                                 / texture->get_width(),
                            .v = ((float)char_info->top)
                                 / texture->get_height(),
                        };
                    }
                }
            }
            if (!texture_)
                texture_ = texture;
            vbo_->apply();
            vbo_->free_cpu_buffer();
            vertex_count_ = vertex_index;
        }
    }

    if (vbo_) {

        texture_->bind(0);

        // LOG("texture_ %d %d", texture_->get_height(), texture_->get_width());

        NX_ASSERT(program_->is_ready(), "gl program not ready");
        program_->use();
        program_->set_uniform_texture("tex", 0);
        program_->set_uniform_vec4("font_color", 1.0, 1.0, 1.0, 1.0);
        program_->set_uniform_vec2("framebuffer_size", size.width, size.height);

        draw_operation_.vertex_buffer = vbo_;
        draw_operation_.texture = texture_;
        draw_operation_.program = program_;
        draw_operation_.primitive = DrawPrimitive::TRIANGLE;
        draw_operation_.polygon_mode = PolygonMode::FILL;
        draw_operation_.strategy = VertexStrategy::POINT_LIST;
        draw_operation_.vertex_count = vertex_count_;

        execute_operation(draw_operation_);
    }
}

} // namespace anyone