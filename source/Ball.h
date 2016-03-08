#pragma once
#include <glm/glm.hpp>
#include <string>

#include "Texture.h"

class SpriteBatch;
class Player;

class Ball
{
public:
    Ball();
    ~Ball();
    void Init(const std::string& filePath, int x, int y);
    void Update(Player& p1, Player& p2);
    void Draw(SpriteBatch& spriteBatch);

private:
    glm::vec2 m_position;
    glm::vec2 m_direction;
    Texture* m_texture;

    int m_width;
    int m_height;

    int m_hitFrames;
};

