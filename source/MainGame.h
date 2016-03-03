#pragma once

#include "Shaders.h"
#include "Camera.h"
#include "SpriteBatch.h"
#include <glm/glm.hpp>
#include <vector>

#include "Texture.h"
#include "Player.h"

#include "SceneManager.h"

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void Run();

private:
    /// Member functions
    bool Init();
    void GameLoop();

    void Draw();
    void Update();

    /// Member variables
    Shaders     m_shaders;
    Camera      m_camera;
    SpriteBatch m_spriteBatch;

    //Player      m_player;
    
    SceneManager* m_sceneManager;
};

