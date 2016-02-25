#pragma once
#include <glm/glm.hpp>
#include <string>

#include "Texture.h"

class SpriteBatch;

class Ball
{
public:
    Ball();
    ~Ball();
    void Init(const std::string& filePath, glm::vec2& position);
    void Update();
    void Draw(SpriteBatch& spriteBatch);

private:
    glm::vec2 m_position;
    Texture* m_texture;
};

