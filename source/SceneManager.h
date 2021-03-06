#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
class Scene;
class SpriteBatch;

class SceneManager
{
public:
    SceneManager(SpriteBatch& spriteBatch);
    ~SceneManager();

    void AddScene(Scene* scene);
    void RemoveScene(std::string name);
    void UpdateScene(const std::vector <glm::vec2>& input);
    void RenderScene();
    void ChangeCurrentScene(std::string name);

private:
    std::vector <Scene*> m_scenes;
    Scene* m_currentScene;

    SpriteBatch& m_spriteBatch;
};

