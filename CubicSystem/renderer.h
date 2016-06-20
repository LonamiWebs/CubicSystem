#pragma once

#include "shader.h"
#include "world.h"
#include "block.h"

class Renderer
{
public:
    Renderer(Shader &shader);
    ~Renderer();

    void DrawWorld(World world, bool useShader = true);
    void DrawBlock(Block block, bool useShader = true);

private:
    Shader shader;
    GLuint VBO, cubeVAO;

    void initRenderData();
};