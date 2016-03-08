#include "Game.h"

#include <glm/glm.hpp>

#define RIGHT 5.0f
#define LEFT -5.0f

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const std::string& name)
{
    m_name = name;
    m_playerOne.Init("sprites/player.png", glm::vec2(0.0f, 700.0f));
    m_playerTwo.Init("sprites/player.png", glm::vec2(0.0f, -700.0f));
    m_ball.Init("sprites/ball.png", 0, 0);
}

void Game::Update(const std::vector <glm::vec2>& input)
{
    // Update players position
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i].y > 0)
        {
            if (input[i].x < 0)
                m_playerOne.Update(LEFT); // Update player to the left
            else
                m_playerOne.Update(RIGHT); // Update player to the right
        }
        else if (input[i].y < 0)
        {
            if (input[i].x < 0)
                m_playerTwo.Update(LEFT); // Update player to the left
            else
                m_playerTwo.Update(RIGHT); // Update player to the right
        }
    }

    // Update ball
    m_ball.Update(m_playerOne, m_playerTwo);
}

void Game::Draw(SpriteBatch& spriteBatch)
{
    m_playerOne.Draw(spriteBatch);
    m_playerTwo.Draw(spriteBatch);
    m_ball.Draw(spriteBatch);
}