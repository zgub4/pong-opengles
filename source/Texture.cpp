#include "Texture.h"

#include "ResourceManager.h"

Texture::Texture(int width, int height, std::string filePath, const Color& color)
    : m_width(width), m_height(height), m_color(color)
{
    m_textureId = ResourceManager::LoadTexture(filePath);
}

Texture::~Texture()
{
}
