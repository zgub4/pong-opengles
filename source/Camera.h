#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    void Init();
    void Update();

    void ConvertScreenToWorld(glm::vec2& mouseCoords);

    // Setters
    void SetPosition(const  glm::vec2& position) { m_position = position; m_needsMatrixUpdate = true; }
    void SetScale(const float& scale) { m_scale = scale; }

    // Getters
    glm::vec2   GetPosition()       const { return m_position; }
    float       GetScale()          const { return m_scale; }
    glm::mat4   GetCameraMatrix()   const { return m_cameraMatrix; }

private:
    bool        m_needsMatrixUpdate;
    float       m_scale;
    glm::vec2   m_position;
    glm::mat4   m_cameraMatrix;
    glm::mat4   m_orthoMatrix;
};

