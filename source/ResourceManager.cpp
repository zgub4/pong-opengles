#include "ResourceManager.h"

#include <fstream>


TextureCache ResourceManager::m_textureCache;

GLuint ResourceManager::LoadTexture(std::string texturePath)
{
    return m_textureCache.GetTexture(texturePath);
}
