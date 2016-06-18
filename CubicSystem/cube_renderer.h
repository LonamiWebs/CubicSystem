#pragma once

#include "shader.h"
#include "texture.h"

class CubeRenderer
{
public:
    CubeRenderer(Shader &shader);
    ~CubeRenderer();

    void DrawCube(Texture2D &texture, glm::vec3 position);

private:
    Shader shader;
    GLuint VBO, cubeVAO;

    void initRenderData();
};