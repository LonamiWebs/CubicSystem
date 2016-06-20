#pragma once

/*
map format:
(1): integer value  : number of non-air blocks
(2): ${1} * 3 float : x, y, z coordinates of the block

example (in binary)
4
-1.0f, 0.0f, 0.0f
 0.0f, 0.0f, 0.0f
 1.0f, 0.0f, 0.0f
 0.0f, 0.0f, 1.0f

*/

#include "world.h"

class WorldLoader
{
public:
    static World Load(const char* file);

private:
    // Don't allow instances
    WorldLoader() { }
};