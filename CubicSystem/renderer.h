#pragma once

#include "shader.h"
#include "world.h"
#include "block.h"

class Renderer
{
public:
    Renderer(Shader &shader);
    ~Renderer();

    void DrawWorld(World world);
    void DrawBlock(Block block);

private:
    Shader shader;
    GLuint VBO, cubeVAO;

    void initRenderData();
};