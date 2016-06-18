#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

// Class used to compile shaders from source and to interop with uniforms
class Shader
{
public:
    // Fields
    GLuint ID;

    // Constructor
    Shader() { }

    // Set the current shader as active
    Shader &Use();

    // Compile shaders from their source
    void Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

    // Interop with uniforms
    void SetFloat    (const GLchar* name, GLfloat   value,                            GLboolean useShader = false);
    void SetInteger  (const GLchar* name, GLint     value,                            GLboolean useShader = false);
    void SetVector2f (const GLchar* name, GLfloat x, GLfloat y,                       GLboolean useShader = false);
    void SetVector2f (const GLchar* name, glm::vec2 value,                            GLboolean useShader = false);
    void SetVector3f (const GLchar* name, GLfloat x, GLfloat y, GLfloat z,            GLboolean useShader = false);
    void SetVector3f (const GLchar* name, glm::vec3 value,                            GLboolean useShader = false);
    void SetVector4f (const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void SetVector4f (const GLchar* name, glm::vec4 value,                            GLboolean useShader = false);
    void SetMatrix4  (const GLchar* name, glm::mat4 value,                            GLboolean useShader = false);

private:
    // Checks for compilation errors
    void checkCompileErrors(GLuint object, std::string type);
};