#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    void Init(int screenWidth, int screenHeight);
    void Update();

    // Setters
    void SetPosition(const  glm::vec2& position) { m_position = position; m_needsMatrixUpdate = true; }
    void SetScale(const float& scale) { m_scale = scale; }

    // Getters
    glm::vec2   GetPosition()       const { return m_position; }
    float       GetScale()          const { return m_scale; }
    glm::mat4   GetCameraMatrix()   const { return m_cameraMatrix; }

private:
    int         m_screenWidth;
    int         m_screenHeight;
    bool        m_needsMatrixUpdate;
    float       m_scale;
    glm::vec2   m_position;
    glm::mat4   m_cameraMatrix;
    glm::mat4   m_orthoMatrix;
};

