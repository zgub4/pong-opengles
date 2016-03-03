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
    void Update(const float& direction);
    void Draw(SpriteBatch& spriteBatch);

    glm::vec2 GetPosition() const { return m_position; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    Texture*    m_texture;
    glm::vec2   m_position;

    int m_width;
    int m_height;
};

