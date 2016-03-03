#pragma once
#include <string>

class SpriteBatch;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual void Init(const std::string& name);
    virtual void Update();
    virtual void Draw(SpriteBatch& spriteBatch);

    std::string GetName() const { return m_name; }

protected:
    std::string m_name;
    //bool m_isActive;
};

