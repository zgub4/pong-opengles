#include "SceneManager.h"

#include "Scene.h"

SceneManager::SceneManager(SpriteBatch& spriteBatch)
    : m_spriteBatch(spriteBatch), m_currentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
    for (auto& i : m_scenes)
        delete i;
}

void SceneManager::AddScene(Scene * scene)
{
    m_scenes.push_back(scene);
    if (m_currentScene == nullptr)
        m_currentScene = scene;
}

void SceneManager::RemoveScene(std::string name)
{
}

void SceneManager::UpdateScene()
{
    m_currentScene->Update();
}

void SceneManager::RenderScene()
{
    m_currentScene->Draw(m_spriteBatch);
}

void SceneManager::ChangeCurrentScene(std::string name)
{
}
