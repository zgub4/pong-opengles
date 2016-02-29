#include "MainGame.h"

#include "IwGL.h"
#include "IwDebug.h"
#include "s3e.h"

#include <iostream>

#include "ResourceManager.h"
#include "Game.h"

MainGame::MainGame()
{

}

MainGame::~MainGame()
{
    //delete m_sprite;
    delete m_sceneManager;
    IwGLTerminate();
}

void MainGame::Run()
{
    if (Init())
    {
        GameLoop();
    }
}

bool MainGame::Init()
{
    // OpenGL ES init
    if (!IwGLInit())
    {
        IwTrace(GL, ("IwGLInit failed.\n"));
        return false;
    }
    
    // Init camera
    m_screenResolution.x = IwGLGetInt(IW_GL_WIDTH);
    m_screenResolution.y = IwGLGetInt(IW_GL_HEIGHT);
    m_camera.Init(m_screenResolution.x, m_screenResolution.y);

    // Shaders init
    if (!m_shaders.Init("shaders/vertShader.vert", "shaders/fragShader.frag"))
    {
        IwTrace(GL, ("Failed to init shaders.\n"));
        return false;
    }
    m_shaders.AddAttribute("vertexPosition");
    m_shaders.AddAttribute("vertexColor");
    m_shaders.AddAttribute("vertexUV");
    m_shaders.LinkShaders();

    // Init sprites
    /*m_sprite = new Sprite();
    m_sprite->Init(-250.0f, 0.0f, 200, 200);*/
    //m_player.Init(glm::vec2(0.0f, 0.0f));

    m_spriteBatch.Init();

    m_sceneManager = new SceneManager(m_spriteBatch);

    Game* game = new Game();
    game->Init("game");

    m_sceneManager->AddScene(game);

    return true;
}

void MainGame::GameLoop()
{
    while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        m_camera.Update();
        Draw();
    }
}

void MainGame::Draw()
{
    glViewport(0, 0, m_screenResolution.x, m_screenResolution.y);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaders.Use();
    // Render code goes here
    glActiveTexture(GL_TEXTURE0);

    //glBindTexture(GL_TEXTURE_2D, m_sprite->GetTexId());

    // Texture uniform
    GLint textureLocation = m_shaders.GetUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    // Camera uniform
    GLint cameraLocation = m_shaders.GetUniformLocation("camera");
    glm::mat4 cameraMatrix = m_camera.GetCameraMatrix();
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    // Draw batch
    m_spriteBatch.Begin();

    m_sceneManager->RenderScene();

    m_spriteBatch.End();
    m_spriteBatch.Render();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    //m_sprite->Draw();

    m_shaders.Unuse();

    IwGLSwapBuffers();
}