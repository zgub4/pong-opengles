#pragma once

#include "IwGL.h"
#include <string>

class Shaders
{
public:
    Shaders();
    ~Shaders();

    bool    Init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    void    AddAttribute(const std::string& attributeName);

    GLint   GetUniformLocation(const std::string& uniformName);

    bool    LinkShaders();

    void    Use();
    void    Unuse();

private:
    bool    CompileShader(const std::string& shaderPath, GLuint& shaderID);

    int     m_attributesNumber;
    GLuint  m_programID;
    GLuint  m_vertexShaderID;
    GLuint  m_fragmentShaderID;
};

