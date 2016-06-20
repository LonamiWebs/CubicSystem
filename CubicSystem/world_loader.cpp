#include "world_loader.h"

#include <fstream>
#include <glm/glm.hpp>

// DELETE AFTER REMOVING COUTS
#include <iostream>

World WorldLoader::Load(const char* filename)
{
    World result;

    std::ifstream file;
    file.open(filename, std::ios::in || std::ios::binary);
    if (file.is_open())
    {
        int blocks;
        file.read((char*)&blocks, sizeof(int));

        result.Blocks.resize(blocks);

        float x, y, z;
        for (int i = 0; i < blocks; i++)
        {
            file.read((char*)&x, sizeof(float));
            file.read((char*)&y, sizeof(float));
            file.read((char*)&z, sizeof(float));

            // For now, they all have the same ID (0)
            result.Blocks.push_back(*new Block(glm::vec3(x, y, z), 0, 0));
        }
    }

    return result;
}
