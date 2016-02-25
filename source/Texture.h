#pragma once

#include "IwGL.h"
#include "Vertex.h"

#include <string>

class Texture
{
public:
    Texture(int width, int height, std::string filePath, const Color& color);
    ~Texture();

    // Getters
    GLuint  GetTextureId() const { return m_textureId; }
    Color   GetColor() const { return m_color; }

    int     m_width;
    int     m_height;

private:
    GLuint  m_textureId;
    Color   m_color;
};

