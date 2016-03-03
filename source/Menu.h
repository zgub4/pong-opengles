#pragma once
#include "Scene.h"
#include "Ball.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

class SpriteBatch;

class Menu : public Scene
{
public:
    Menu();
    ~Menu();

    void Init(const std::string& name) final override;
    void Update(const std::vector <glm::vec2>& input) final override;
    void Draw(SpriteBatch& spriteBatch) final override;

private:
};

