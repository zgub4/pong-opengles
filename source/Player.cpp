#include "Player.h"

#include "SpriteBatch.h"
#include "Globals.h"

Player::Player()
{
}


Player::~Player()
{
    delete m_texture;
}

void Player::Init(const std::string& filePath, glm::vec2 position)
{
    m_position = position;
    Color color(0, 0, 0, 255);
    m_texture = new Texture(200, 50, filePath, color);
    m_width = m_texture->m_width;
    m_height = m_texture->m_height;
}

void Player::Update(const float& direction)
{
    m_position.x += direction;
    //printf("Player position: %f    %f\n", m_position.x, m_position.y);
}

void Player::Draw(SpriteBatch& spriteBatch)
{
    glm::vec4 destRect(m_position, m_texture->m_width, m_texture->m_height);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    spriteBatch.Draw(destRect, uvRect, m_texture->GetTextureId(), 0.0f, m_texture->GetColor());
}
