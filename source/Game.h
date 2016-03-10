#pragma once
#include "Player.h"
#include "Ball.h"
#include "Scene.h"

#include <string>

class Game : public Scene
{
public:
    Game();
    ~Game();

    void Init(const std::string& name) final override;
    void Update(const std::vector <glm::vec2>& input) final override;
    void Draw(SpriteBatch& spriteBatch) final override;

private:
    Player m_playerOne;
    Player m_playerTwo;
    Ball   m_ball;

    int m_p1score;
    int m_p2score;
};