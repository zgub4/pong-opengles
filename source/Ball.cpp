#include "Ball.h"

#include "Vertex.h"
#include "SpriteBatch.h"

Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::Init(const std::string& filePath, glm::vec2& position)
{
    m_position = position;
    Color color(255, 255, 255, 255);
    m_texture = new Texture(50, 50, filePath, color);
}

void Ball::Update()
{
}

void Ball::Draw(SpriteBatch& spriteBatch)
{
    glm::vec4 destRect(m_position, m_texture->m_width, m_texture->m_height);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    spriteBatch.Draw(destRect, uvRect, m_texture->GetTextureId(), 1.0f, m_texture->GetColor());
}
