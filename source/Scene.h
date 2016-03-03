#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

class SpriteBatch;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual void Init(const std::string& name);
    virtual void Update(const std::vector <glm::vec2>& input);
    virtual void Draw(SpriteBatch& spriteBatch);

    std::string GetName() const { return m_name; }

protected:
    std::string m_name;
    //bool m_isActive;
};

