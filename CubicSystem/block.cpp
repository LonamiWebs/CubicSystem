#include "block.h"

Block::Block(glm::vec3 position, int id, int subId)
    : Position(position), ID(id), SubID(subId)
{
    Texture = ResourceManager::GetTexture(IDToName(id));
}

std::string Block::IDToName(int id)
{
    switch (id)
    {
    case 0:  return "rock";
    default: return "(unnamed)";
    }
}
