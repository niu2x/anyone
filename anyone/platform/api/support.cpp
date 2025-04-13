// #include "main/core.h"
#include "support.h"

namespace anyone {

class DummyVertexBuffer : public VertexBuffer {
public:
    DummyVertexBuffer() { }
    ~DummyVertexBuffer() { }
    void apply() override { }
    void bind() override { }
};

class DummyIndiceBuffer : public IndiceBuffer {
public:
    DummyIndiceBuffer() { }
    ~DummyIndiceBuffer() { }
    void apply() override { }
    void bind() override { }
};

class DummyTexture2D : public Texture2D {
public:
    DummyTexture2D() { }
    ~DummyTexture2D() { }
    void apply() override { }
    void bind(int tex_unit) override { (void)tex_unit; }
};

class DummyCubeMap : public CubeMap {
public:
    DummyCubeMap() { }
    ~DummyCubeMap() { }
    void apply() override { }
    void bind(int tex_unit) override { (void)tex_unit; }
};

class DummyProgram : public Program {
public:
    DummyProgram() { }
    ~DummyProgram() { }
    void use() override { }
    void set_param_texture(const char* name, int tex_unit) override
    {
        (void)name;
        (void)tex_unit;
    }

    void set_param_int(const char* name, int arg) override
    {
        (void)name;
        (void)arg;
    }

    void set_param_float(const char* name, float arg) override
    {
        (void)name;
        (void)arg;
    }

    void set_param_vec2(const char* name, const float args[]) override
    {
        (void)name;
        (void)args;
    }
    void set_param_vec3(const char* name, const float args[]) override
    {
        (void)name;
        (void)args;
    }
    void set_param_vec4(const char* name, const float args[]) override
    {
        (void)name;
        (void)args;
    }

    void set_param_mat4(const char* name, const float args[]) override
    {
        (void)name;
        (void)args;
    }
};

PlatformSupport::~PlatformSupport() { }

void RenderAPI::draw(const DrawOperation& op)
{
    (void)op;
    frame_stats_->draw_call++;
}

FrameStats init_frame_stats;

RenderAPI::RenderAPI() : frame_stats_(&init_frame_stats) { }

RenderAPI::~RenderAPI() { }

void RenderAPI::clear() { }

void RenderAPI::set_clear_color(const Color& color) { (void)color; }

VertexBuffer* RenderAPI::create_vertex_buffer()
{
    return new DummyVertexBuffer;
}
void RenderAPI::destroy_vertex_buffer(VertexBuffer* vbo) { delete vbo; }

IndiceBuffer* RenderAPI::create_indice_buffer()
{
    return new DummyIndiceBuffer;
}
void RenderAPI::destroy_indice_buffer(IndiceBuffer* vbo) { delete vbo; }

Texture2D* RenderAPI::create_texture_2d() { return new DummyTexture2D; }
void RenderAPI::destroy_texture_2d(Texture2D* tex) { delete tex; }

CubeMap* RenderAPI::create_cube_map() { return new DummyCubeMap; }
void RenderAPI::destroy_cube_map(CubeMap* tex) { delete tex; }

Program* RenderAPI::create_rml_ui_program() { return new DummyProgram; }
Program* RenderAPI::create_sky_box_program() { return new DummyProgram; }
Program* RenderAPI::create_model_program() { return new DummyProgram; }

void RenderAPI::destroy_program(Program* program) { delete program; }

void RenderAPI::set_blend_type(BlendType b) { (void)b; }
void RenderAPI::set_depth_test(bool b) { (void)b; }

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

Texture2D::Texture2D()
: width_(0)
, height_(0)
, pixel_format_(PixelFormat::RGBA_U8)
{
}

Texture2D::~Texture2D() { }

void Texture2D::alloc_cpu_buffer(int w, int h)
{
    width_ = w;
    height_ = h;
    auto& pf_desc = get_pixel_format_desc(pixel_format_);
    cpu_buffer_.resize(width_ * height_ * pf_desc.num_channel
                       * pf_desc.elem_size);
}

void Texture2D::free_cpu_buffer() { cpu_buffer_.clear(); }

Program::Program() { }

Program::~Program() { }

static PixelFormatDescription pixel_format_desc_list[] = {
    { .num_channel = 4, .elem_size = 1 },
    { .num_channel = 3, .elem_size = 1 },
};

const PixelFormatDescription& get_pixel_format_desc(PixelFormat fmt)
{
    return pixel_format_desc_list[(int)fmt];
}

CubeMap::CubeMap() : edge_(0), pixel_format_(PixelFormat::RGBA_U8) { }

CubeMap::~CubeMap() { }

void CubeMap::alloc_cpu_buffer(int edge)
{
    edge_ = edge;
    cpu_buffer_.resize(6 * get_one_face_bytes());
}

size_t CubeMap::get_one_face_bytes() const
{
    auto& pf_desc = get_pixel_format_desc(pixel_format_);
    return edge_ * edge_ * pf_desc.num_channel * pf_desc.elem_size;
}

void CubeMap::free_cpu_buffer() { cpu_buffer_.clear(); }

} // namespace anyone