#pragma once

#include "IwGL.h"

#include "TextureCache.h"
#include "Texture.h"

#include <map>
#include <string>

class ResourceManager
{
public:
    static GLuint LoadTexture(std::string texturePath);

private:
    static TextureCache m_textureCache;
};

