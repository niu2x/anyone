#include "texture_loader.h"
#include <turbojpeg.h>
#include "core.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

CubeMap* TextureLoader::load_cube_map_png(const String& uri)
{
    String px_uri = nx::fs::join_path(uri, "px.png");
    auto px_data = GET_CORE()->read_file_data(px_uri);
    if (!px_data) {
        return nullptr;
    }

    int width, height, channels_in_file;

    auto stbi_handle = stbi_load_from_memory(px_data->data(),
                                             px_data->size(),
                                             &width,
                                             &height,
                                             &channels_in_file,
                                             4);
    NX_ASSERT(width == height, "cubemap's width should equal to height");

    LOG("cubemap edge %d", width);

    auto cube_map = GET_RENDER_API()->create_cube_map();
    cube_map->alloc_cpu_buffer(width);
    memcpy(cube_map->get_cpu_buffer(0),
           stbi_handle,
           cube_map->get_one_face_bytes());
    stbi_image_free(stbi_handle);

    const char* others[] = { "px.png", "nx.png", "py.png",
                             "ny.png", "pz.png", "nz.png" };
    for (int i = 1; i < 6; i++) {
        String p_uri = nx::fs::join_path(uri, others[i]);
        auto p_data = GET_CORE()->read_file_data(p_uri);
        if (!p_data) {
            return nullptr;
        }
        auto stbi_handle = stbi_load_from_memory(p_data->data(),
                                                 p_data->size(),
                                                 &width,
                                                 &height,
                                                 &channels_in_file,
                                                 4);
        memcpy(cube_map->get_cpu_buffer(i),
               stbi_handle,
               cube_map->get_one_face_bytes());
        stbi_image_free(stbi_handle);
    }

    cube_map->apply();
    cube_map->free_cpu_buffer();

    return cube_map;
}

} // namespace anyone