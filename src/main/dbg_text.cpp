#include "dbg_text.h"

namespace anyone {

DebugText::DebugText(Font* font)
: font_(font)
, dirty_(true)
, vbo_(nullptr)
, vertex_count_(0)
, texture_(nullptr)
{
    auto size = GET_CORE()->get_framebuffer_size();
    screens_.resize((size.width / 32) * (size.height * 32));
    memset(screens_.data(), 0, screens_.size());
    // screens_[0] = 'A';
    // screens_[1] = 'B';
}

DebugText::~DebugText()
{
    if (vbo_)
        delete vbo_;
}

struct Vertex {
    float x, y;
    float u, v;
};

void DebugText::printf(int x, int y, const char* msg)
{
    auto size = GET_CORE()->get_framebuffer_size();
    int cell_width = (size.width / 32);
    int cell_height = (size.height / 32);

    for (int i = 0; i < strlen(msg); i++) {
        if (x + i >= 0 && x + i < cell_width) {
            screens_[x + i + y * cell_width] = msg[i];
        }
    }
}

void DebugText::render()
{
    auto size = GET_CORE()->get_framebuffer_size();

    if (dirty_) {
        dirty_ = false;

        if (vbo_) {
            delete vbo_;
            vbo_ = nullptr;
        }

        int chars_counter = 0;
        GL_Texture2D* texture;

        for (int i = 0; i < screens_.size(); i++) {
            char c = screens_[i];
            if (c) {
                auto x = i % (size.width / 32);
                auto y = i / (size.width / 32);
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

                        auto cell_x = i % (size.width / 32);
                        auto cell_y = i / (size.width / 32);

                        vertexs[vertex_index++] = {
                            .x = cell_x * 32,
                            .y = cell_y * 32,
                            .u = ((float)char_info->left)
                                 / texture->get_width(),
                            .v = ((float)char_info->top)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * 32,
                            .y = cell_y * 32 + char_info->height,
                            .u = ((float)char_info->left)
                                 / texture->get_width(),
                            .v = ((float)char_info->top + char_info->height)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * 32 + char_info->width,
                            .y = cell_y * 32 + char_info->height,
                            .u = ((float)char_info->left + char_info->width)
                                 / texture->get_width(),
                            .v = ((float)char_info->top + char_info->height)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * 32,
                            .y = cell_y * 32,
                            .u = ((float)char_info->left)
                                 / texture->get_width(),
                            .v = ((float)char_info->top)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * 32 + char_info->width,
                            .y = cell_y * 32 + char_info->height,
                            .u = ((float)char_info->left + char_info->width)
                                 / texture->get_width(),
                            .v = ((float)char_info->top + char_info->height)
                                 / texture->get_height(),
                        };

                        vertexs[vertex_index++] = {
                            .x = cell_x * 32 + char_info->width,
                            .y = cell_y * 32,
                            .u = ((float)char_info->left + char_info->width)
                                 / texture->get_width(),
                            .v = ((float)char_info->top)
                                 / texture->get_height(),
                        };
                    }
                }
            }
            texture_ = texture;
            vbo_->apply();
            vbo_->free_cpu_buffer();
            vertex_count_ = vertex_index;
        }
    }

    if (vbo_) {
        vbo_->bind();
        texture_->bind(0);
        auto program = GET_CORE()->get_dbg_text_program();
        NX_ASSERT(program->is_ready(), "gl program not ready");

        program->use();
        program->set_uniform_texture("tex", 0);
        program->set_uniform_vec2("framebuffer_size", size.width, size.height);
        glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
    }
}

} // namespace anyone