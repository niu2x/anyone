// #include "main/core.h"
#include "support.h"

namespace anyone {

PlatformSupport::~PlatformSupport() { }

void RenderAPI::draw(const DrawOperation& op)
{
    (void)op;
    frame_stats_->draw_call++;
}

FrameStats init_frame_stats;

RenderAPI::RenderAPI() : frame_stats_(&init_frame_stats) { }

RenderAPI::~RenderAPI() { }

VertexBuffer::VertexBuffer() : buf_size_(0) { }

VertexBuffer::~VertexBuffer() { }

void VertexBuffer::alloc_cpu_buffer(size_t size)
{
    buf_size_ = size;
    cpu_buffer_.resize(buf_size_);
}

void VertexBuffer::free_cpu_buffer() { cpu_buffer_.clear(); }

void VertexBuffer::set_vertex_layout(const VertexLayout& layout)
{
    vertex_layout_ = layout;
}

IndiceBuffer::IndiceBuffer() { }

IndiceBuffer::~IndiceBuffer() { }

void IndiceBuffer::alloc_cpu_buffer(size_t indice_count)
{
    count_ = indice_count;
    cpu_buffer_.resize(indice_count);
}

void IndiceBuffer::free_cpu_buffer() { cpu_buffer_.clear(); }

Texture2D::Texture2D() : width_(0), height_(0) { }

Texture2D::~Texture2D() { }

void Texture2D::alloc_cpu_buffer(int w, int h)
{
    width_ = w;
    height_ = h;
    cpu_buffer_.resize(width_ * height_ * 4);
}

void Texture2D::free_cpu_buffer() { cpu_buffer_.clear(); }

Program::Program() { }

Program::~Program() { }

} // namespace anyone