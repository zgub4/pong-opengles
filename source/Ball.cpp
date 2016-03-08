#include "Ball.h"

#include "Vertex.h"
#include "SpriteBatch.h"
#include "Player.h"

#include "Globals.h"
Ball::Ball() : m_hitFrames(100)
{
}


Ball::~Ball()
{
}

void Ball::Init(const std::string& filePath, int x, int y)
{
    m_position = glm::vec2(x, y);
    Color color(255, 255, 255, 255);
    m_texture = new Texture(50, 50, filePath, color);
    m_direction = glm::vec2(1.0f, 1.0f);
    m_width = m_texture->m_width;
    m_height = m_texture->m_height;
}

void Ball::Update(Player& p1, Player& p2)
{
    //printf("Ball position: %f   %f\n", m_position.x, m_position.y);
    
    // Update ball position
    m_position += m_direction * 2.0f;

    // Check for collision after at least 30 frames passed
    if (m_hitFrames > 30)
    {
        // Check wall collision
        if (m_position.x < -Globals::ScreenResolution.x / 2 || m_position.x > Globals::ScreenResolution.x / 2 - m_width)
            m_direction.x = -m_direction.x;
        else if (m_position.y < -Globals::ScreenResolution.y / 2 || m_position.y > Globals::ScreenResolution.y / 2 - m_height)
            m_direction.y = -m_direction.y;

        // Check player collision
        glm::vec2 p1pos = p1.GetPosition();
        glm::vec2 p2pos = p2.GetPosition();

        //printf("Player position: %f   %f\n", p1pos.x, p1pos.y);

        if (m_position.y > 0) // We consider ball is on top half
        {
            if (p1pos.y > p2pos.y) // This means player one is the top one
            {
                if (m_position.y >= p1pos.y - p1.GetHeight() && m_position.y <= p1pos.y) // We are good in X axis
                    if (m_position.x + m_width >= p1pos.x && m_position.x <= p1pos.x + p1.GetWidth())
                    {
                        m_direction.y = -m_direction.y;
                        m_hitFrames = 0;
                    }
            }
            else // This means player two is the top one
            {
                if (m_position.y >= p1pos.y - p1.GetHeight() && m_position.y <= p1pos.y) // We are good in X axis
                    if (m_position.x + m_width >= p1pos.x && m_position.x <= p1pos.x + p1.GetWidth())
                    {
                        m_direction.y = -m_direction.y;
                        m_hitFrames = 0;
                    }
            }
        }
        else // We consider ball is on bottom half
        {
            if (p1pos.y > p2pos.y) // This means player one is the top one
            {
                if (m_position.y <= p1pos.y && m_position.y >= p1pos.y + p1.GetHeight()) // We are good in X axis
                    if (m_position.x + m_width >= p1pos.x && m_position.x <= p1pos.x + p1.GetWidth())
                    {
                        m_direction.y = -m_direction.y;
                        m_hitFrames = 0;
                    }
            }
            else // This means player two is the top one
            {
                if (m_position.y <= p1pos.y && m_position.y >= p1pos.y + p1.GetHeight()) // We are good in X axis
                    if (m_position.x + m_width >= p1pos.x && m_position.x <= p1pos.x + p1.GetWidth())
                    {
                        m_direction.y = -m_direction.y;
                        m_hitFrames = 0;
                    }
            }
        }
    }
    m_hitFrames++;
    //printf("Ball position: %f   %f\n", m_position.x, m_position.y);
}

void Ball::Draw(SpriteBatch& spriteBatch)
{
    glm::vec4 destRect(m_position, m_texture->m_width, m_texture->m_height);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    spriteBatch.Draw(destRect, uvRect, m_texture->GetTextureId(), 1.0f, m_texture->GetColor());
}
