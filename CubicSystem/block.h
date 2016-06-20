#pragma once

#include <string>
#include <glm/glm.hpp>

#include "texture.h"
#include "resource_manager.h"

class Block
{
public:
    int ID;
    int SubID;
    glm::vec3 Position;
    Texture2D Texture;

    Block() : Position(glm::vec3()), ID(-1), SubID(-1) { }
    Block(glm::vec3 position, int id, int subId);

    static std::string IDToName(int id);
};