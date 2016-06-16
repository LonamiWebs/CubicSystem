#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
    // Program ID
    GLuint Program;
    // Shader constructor, takes two files corresponding to both the vertex and fragment shaders
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Uses the shader (setting the program as active)
    void Use();
    // Gets an uniform
    GLint GetUniform(const GLchar* name);
};