#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>

enum BlockID
{
    BI_Air,
    BI_Dirt,
    BI_Grass
};

typedef struct
{
    const char *name;
    int isSolid;
    int textureIndex;

    void (*onBreak)(void);
    void (*onPlace)(void);
} BlockDefinition;

#endif