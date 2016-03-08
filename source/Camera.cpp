#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Globals.h"

Camera::Camera()
    : m_scale(1.0f), m_needsMatrixUpdate(true), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_position(0.0f, 0.0f)
{
}


Camera::~Camera()
{
}

void Camera::Init()
{
    m_orthoMatrix = glm::ortho(0.0f, (float)Globals::ScreenResolution.x, 0.0f, (float)Globals::ScreenResolution.y);
}

void Camera::Update()
{
    if (m_needsMatrixUpdate)
    {
        // Camera translation
        glm::vec3 translate(-m_position.x + Globals::ScreenResolution.x / 2, -m_position.y + Globals::ScreenResolution.y / 2, 0.0f);
        m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

        // Camera scale
        glm::vec3 scale(m_scale, m_scale, 0.0f);
        m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

        m_needsMatrixUpdate = false;
    }
}

void Camera::ConvertScreenToWorld(glm::vec2& mouseCoords)
{
    mouseCoords.y = Globals::ScreenResolution.y - mouseCoords.y;
    mouseCoords -= glm::vec2(Globals::ScreenResolution.x / 2, Globals::ScreenResolution.y / 2);
    mouseCoords /= m_scale;
    mouseCoords += m_position;
}
