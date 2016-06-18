#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <SOIL.h>

// Instantiate variables
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadShader(const GLchar* file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
{
    // Define variables
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    
    try
    {
        // Vertex
        std::ifstream vertexShaderFile(vShaderFile);
        std::stringstream vShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        vertexShaderFile.close();

        vertexCode = vShaderStream.str();

        // Fragment
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream fShaderStream;

        fShaderStream << fragmentShaderFile.rdbuf();
        fragmentShaderFile.close();

        fragmentCode = fShaderStream.str();

        // Geometry
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;

            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();

            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    
    Shader shader;
    shader.Compile(vertexCode.c_str(), fragmentCode.c_str(), gShaderFile != nullptr ? geometryCode.c_str() : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.InternalFormat = GL_RGBA;
        texture.ImageFormat = GL_RGBA;
    }
    // Load image and generate texture, then clear resources
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.ImageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    texture.Generate(width, height, image);
    SOIL_free_image_data(image);

    return texture;
}
