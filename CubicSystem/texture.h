#pragma once

#include <GL/glew.h>

class Texture2D
{
public:
    // Fields
    GLuint ID;
    GLuint Width, Height;

    // Texture format and image format
    GLuint InternalFormat;
    GLuint ImageFormat;

    // Wrapping and filter modes
    GLuint WrapS;
    GLuint WrapT;
    GLuint FilterMin;
    GLuint FilterMax;

    // Constructor
    Texture2D();

    // Generates textures from image data
    void Generate(GLuint width, GLuint height, unsigned char* data);

    // Binds the current texture as active GL_TEXTURE_2D texture object
    void Bind() const;
};