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

protected:
    unsigned int m_nameHash;
    //bool m_isActive;
};

