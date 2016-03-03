#include "Menu.h"

#include <glm/glm.hpp>

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::Init(const std::string & name)
{
    m_name = name;
    m_ball = new Ball();
    m_ball->Init("sprites/ball.png", glm::vec2(0.0f, 0.0f));
}

void Menu::Update()
{
}

void Menu::Draw(SpriteBatch & spriteBatch)
{
    m_ball->Draw(spriteBatch);
}
