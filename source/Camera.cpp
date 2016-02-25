#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : m_screenWidth(0), m_screenHeight(0), m_scale(1.0f), m_needsMatrixUpdate(true),
    m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_position(0.0f, 0.0f)
{
}


Camera::~Camera()
{
}

void Camera::Init(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
}

void Camera::Update()
{
    if (m_needsMatrixUpdate)
    {
        // Camera translation
        glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
        m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

        // Camera scale
        glm::vec3 scale(m_scale, m_scale, 0.0f);
        m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

        m_needsMatrixUpdate = false;
    }
}
