#pragma once
#include <map>
#include <string>

#include "IwGL.h"
#include "Texture.h"

class TextureCache
{
public:
    TextureCache();
    ~TextureCache();

    GLuint GetTexture(std::string texturePath);

private:
    GLuint LoadPng(const char* texturePath, int* width, int* height);

    std::map <std::string, GLuint> m_textureMap;
};

