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
    void Update() final override;
    void Draw(SpriteBatch& spriteBatch) final override;

private:
    Player m_playerOne;
    Player m_playerTwo;
    Ball   m_ball;
};