#include "support.h"

namespace anyone {

PlatformSupport::~PlatformSupport() { }

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

} // namespace anyone