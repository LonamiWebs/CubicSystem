#pragma once

#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:
    // Store the resources
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;

    // Loads and generates shaders from files. The geometry shader file can be left as nullptr
    static Shader LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
    // Retrieves a stored shader
    static Shader GetShader(std::string name);

    // Loads and generates textures from files
    static Texture2D LoadShader(const GLchar* file, GLboolean alpha, std::string name);
    // Retrieves a stored texture
    static Texture2D GetTexture(std::string name);

    // Clear used resources
    static void Clear();
private:
    // Don't allow instances
    ResourceManager() { }

    // Load from files
    static Shader loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile);
    static Texture2D loadTextureFromFile(const GLchar* file, GLboolean alpha);
};