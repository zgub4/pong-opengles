#pragma once

#include "Texture.h"
#include <glm/glm.hpp>

#include <string>

class SpriteBatch;

class Player
{
public:
    Player();
    ~Player();

    void Init(const std::string& filePath, glm::vec2 position);
    void Update();
    void Draw(SpriteBatch& spriteBatch);

private:
    Texture*    m_texture;
    glm::vec2   m_position;
};

