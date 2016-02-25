#include "TextureCache.h"

#include <png.h>
#include <fstream>

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLuint TextureCache::GetTexture(std::string texturePath)
{
    auto it = m_textureMap.find(texturePath);
    if (it == m_textureMap.end())
    {
        int width, height;
        GLuint newTextureId = LoadPng(texturePath.c_str(), &width, &height);
        m_textureMap.insert(std::make_pair(texturePath, newTextureId));
        return newTextureId;
    }
    return it->second;
}

GLuint TextureCache::LoadPng(const char* texturePath, int* width, int* height)
{
    png_byte header[8];

    FILE* fp = fopen(texturePath, "rb");
    if (fp == NULL)
    {
        perror(texturePath);
        return 0;
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "error: %s is not a PNG.\n", texturePath);
        fclose(fp);
        return 0;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "error: png_create_read_struct returned 0.\n");
        fclose(fp);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct retruned 0.\n");
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(fp);
        return 0;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // Init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);

    // sets outside variables width and height values 
    if (width)
        *width = temp_width;
    if (height)
        *height = temp_height;

    if (bit_depth != 8)
    {
        fprintf(stderr, "%s: Unsupported bit depth %d. Must be 8.\n", texturePath, bit_depth);
        return 0;
    }

    GLint format;
    switch (color_type)
    {
    case PNG_COLOR_TYPE_RGB:
        format = GL_RGB;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        format = GL_RGBA;
        break;
    default:
        fprintf(stderr, "%s: Uknown libpng color type %d.\n", texturePath, color_type);
        return 0;
    }

    // Update the png info struct
    png_read_update_info(png_ptr, info_ptr);

    // row size in bytes
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires row to be 4 byte alligned
    rowbytes += 3 - ((rowbytes - 1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte* image_data = (png_byte*)malloc(rowbytes * temp_height * sizeof(png_byte) + 15);
    if (image_data == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for png image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_byte** row_pointers = (png_byte**)malloc(temp_height * sizeof(png_byte*));
    if (row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for png row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    for (unsigned int i = 0; i < temp_height; i++)
    {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // Generate the OpenGL texture object
    GLuint texture;

    // Generate the opengles texture object
    glGenTextures(1, &texture);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    // Upload the pixels to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);

    // Set texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(fp);

    // Adding texture instance to textures map
    m_textureMap.insert(std::make_pair(texturePath, texture));

    // Returns texture id as instance
    return texture;
}
