#pragma 
#include "Scene.h"
#include "Ball.h"

#include <string>

class SpriteBatch;

class Menu : public Scene
{
public:
    Menu();
    ~Menu();

    void Init(const std::string& name) final override;
    void Update() final override;
    void Draw(SpriteBatch& spriteBatch) final override;

private:
    Ball* m_ball;
};

