#include "Shaders.h"

#include <iostream> // just for print errors into console
#include <fstream>
#include <vector>

Shaders::Shaders()
    : m_attributesNumber(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
{
}


Shaders::~Shaders()
{
}

bool Shaders::Init(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
    m_programID = glCreateProgram();

    // Create vertex shader object and store its ID
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0)
    {
        std::cout << "Vertex shader failed to be created (Shaders.cpp, 25).\n";
        return false;
    }

    // Create fragment shader object and store its ID
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0)
    {
        std::cout << "Fragment shader failed to be created (Shaders.cpp. 33).\n";
        return false;
    }

    if (!CompileShader(vertexShaderPath, m_vertexShaderID))
    {
        std::cout << "Failed to compile vertex shader (Shaders.cpp, 39).\n";
        return false;
    }

    if (!CompileShader(fragmentShaderPath, m_fragmentShaderID))
    {
        std::cout << "Failed to compile fragment shader (Shaders.cpp, 45).\n";
        return false;
    }

    return true;
}

void Shaders::AddAttribute(const std::string & attributeName)
{
    glBindAttribLocation(m_programID, m_attributesNumber++, attributeName.c_str());
}

GLint Shaders::GetUniformLocation(const std::string & uniformName)
{
    GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX)
    {
        std::cout << "Failed to get uniform location (Shaders.cpp, 62).\n";
    }
    return location;
}

void Shaders::Use()
{
    glUseProgram(m_programID);
    for (int i = 0; i < m_attributesNumber; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

void Shaders::Unuse()
{
    glUseProgram(0);
    for (int i = 0; i < m_attributesNumber; i++)
    {
        glDisableVertexAttribArray(i);
    }
}

bool Shaders::CompileShader(const std::string & shaderPath, GLuint & shaderID)
{
    std::ifstream shaderFile(shaderPath);
    if (shaderFile.fail())
    {
        std::cout << "Could not open " + shaderPath + " file (Shaders.cpp, 80).\n";
        return false;
    }

    std::string fileContents = "";
    std::string line;

    while(std::getline(shaderFile, line))
    {
        fileContents += line;
    }
    shaderFile.close();

    const char* contentsPtr = fileContents.c_str();
    
    glShaderSource(shaderID, 1, &contentsPtr, nullptr);
    glCompileShader(shaderID);

    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE)
    {
        GLint maxLenght = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLenght);

        std::vector <char> errorLog(maxLenght);
        glGetShaderInfoLog(shaderID, maxLenght, &maxLenght, &errorLog[0]);

        glDeleteShader(shaderID);

        std::cout << std::string(&errorLog[0]) << std::endl;
        return false;
    }

    return true;
}

bool Shaders::LinkShaders()
{
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    glLinkProgram(m_programID);

    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLenght = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLenght);

        std::vector <char> errorLog(maxLenght);
        glGetProgramInfoLog(m_programID, maxLenght, &maxLenght, &errorLog[0]);


        glDeleteProgram(m_programID);
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);

        std::cout << (std::string)&errorLog[0] << std::endl;
        return false;
    }

    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);

    return true;
}
