#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

enum BlockID
{
    BI_Air,
    BI_Dirt,
    BI_Grass,
    BI_Stone,
};

struct BlockDefinition
{
    const char *name;
    int isSolid;
    Vector2 textureIndex;

    void (*onBreak)(void);
    void (*onPlace)(void);
};

struct BlockRegistry
{
    struct BlockDefinition registry[256];
    unsigned char blockCount;
};

struct BlockRegistry CreateBlockRegistry();
int RegisterBlock(struct BlockRegistry *blockRegistry, struct BlockDefinition blockDefinition);
int InitializeBlockRegistry(struct BlockRegistry *blockRegistry);

#endif