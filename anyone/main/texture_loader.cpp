#include "texture_loader.h"
#include <turbojpeg.h>
#include "core.h"

namespace anyone {

Texture2D* TextureLoader::load_2d_jpg(const uint8_t* data, size_t len)
{

    tjhandle jpeg_decompressor = tjInitDecompress();
    if (!jpeg_decompressor) {
        return nullptr;
    }

    // 获取 JPEG 图像的宽度、高度和子采样因子
    int width, height, jpeg_subsamp;
    if (tjDecompressHeader2(jpeg_decompressor,
                            (uint8_t*)data,
                            len,
                            &width,
                            &height,
                            &jpeg_subsamp)
        != 0) {
        tjDestroy(jpeg_decompressor);
        return nullptr;
    }

    // 创建 Texture2D 对象
    Texture2D* texture = GET_RENDER_API()->create_texture_2d();
    texture->set_pixel_format(PixelFormat::RGB_U8);
    texture->alloc_cpu_buffer(width, height);

    // 解码 JPEG 图像数据
    if (tjDecompress2(jpeg_decompressor,
                      data,
                      len,
                      texture->get_cpu_buffer(),
                      width,
                      0,
                      height,
                      TJPF_RGB,
                      0)
        != 0) {
        GET_RENDER_API()->destroy_texture_2d(texture);
        tjDestroy(jpeg_decompressor);
        return nullptr;
    }

    texture->apply();
    texture->free_cpu_buffer();

    tjDestroy(jpeg_decompressor);
    return texture;
}

} // namespace anyone