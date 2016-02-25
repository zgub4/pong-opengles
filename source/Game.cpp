#include "Game.h"

#include <glm/glm.hpp>

Game::Game()
{
}


Game::~Game()
{
}

void Game::Init(const std::string& name)
{
    m_playerOne.Init("sprites/player.png", glm::vec2(0.0f, -200.0f));
    m_playerTwo.Init("sprites/player.png", glm::vec2(0.0f, 200.0f));
    m_ball.Init("sprites/ball.png", glm::vec2(0.0f, 0.0f));
}

void Game::Update()
{
    m_playerOne.Update();
    m_playerTwo.Update();
    m_ball.Update();
}

void Game::Draw(SpriteBatch& spriteBatch)
{
    m_playerOne.Draw(spriteBatch);
    m_playerTwo.Draw(spriteBatch);
    m_ball.Draw(spriteBatch);
}