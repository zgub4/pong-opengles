#include "MainGame.h"

#include "IwGL.h"
#include "IwDebug.h"
#include "s3e.h"

#include <iostream>

#include "ResourceManager.h"
#include "Game.h"
#include "Menu.h"

#include "Globals.h"

MainGame::MainGame()
{

}

MainGame::~MainGame()
{
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
    Globals::ScreenResolution = glm::ivec2(IwGLGetInt(IW_GL_WIDTH), IwGLGetInt(IW_GL_HEIGHT));
    m_camera.Init();

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

    Globals::g_input = new Input();

    m_spriteBatch.Init();

    m_sceneManager = new SceneManager(m_spriteBatch);

    Game* game = new Game();
    game->Init("game");

    m_sceneManager->AddScene(game);

    Menu* menu = new Menu();
    menu->Init("menu");

    m_sceneManager->AddScene(menu);

    return true;
}

void MainGame::GameLoop()
{
    while (!s3eDeviceCheckQuitRequest())
    {
        // Update the input systems
        Globals::g_input->Update();

        // Update camera position
        m_camera.Update();

        // Update objects
        Update();

        // Render objects
        Draw();
    }
}

void MainGame::Draw()
{
    glViewport(0, 0, Globals::ScreenResolution.x, Globals::ScreenResolution.y);
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

void MainGame::Update()
{
    // Process input
    std::vector <glm::vec2> touches;
    for (size_t i = 0; i < S3E_POINTER_TOUCH_MAX; i++)
    {
        if (Globals::g_input->TouchMap[i] == true)
        {
            glm::vec2 touchPos = glm::vec2(s3ePointerGetTouchX(i), s3ePointerGetTouchY(i));
            m_camera.ConvertScreenToWorld(touchPos);
            touches.push_back(touchPos);
            //printf("%f   %f\n", touchPos.x, touchPos.y);
        }
    }
    m_sceneManager->UpdateScene(touches);
}
