#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

//Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
//{
//}
//
//void Shader::Use() { glUseProgram(Program); }
//
//GLint Shader::GetUniform(const GLchar* name) { return glGetUniformLocation(Program, name); }

Shader &Shader::Use()
{
    glUseProgram(ID);
    return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
    GLuint sVertex, sFragment, sGeometry;
    // Create compile and check vertex shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    // Create compile and check fragment shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    // Create compile and check geomtry shader, if source was provided
    if (geometrySource != nullptr)
    {
        sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(sGeometry, 1, &geometrySource, NULL);
        glCompileShader(sGeometry);
        checkCompileErrors(sGeometry, "GEOMETRY");
    }

    // Link shaders in our new shader program
    ID = glCreateProgram();

    glAttachShader(ID, sVertex);
    glAttachShader(ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(ID, sGeometry);

    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Clean up resources
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(sGeometry);
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::SetVector2f(const GLchar* name, glm::vec2 value, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::SetVector3f(const GLchar* name, glm::vec3 value, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, glm::vec4 value, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar* name, glm::mat4 value, GLboolean useShader)
{
    if (useShader)
        Use();
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED" << std::endl << infoLog;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << infoLog;
        }
    }
}
