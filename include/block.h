#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

typedef enum
{
    BI_Air,
    BI_Dirt,
    BI_Grass,
    BI_Stone,
} BlockID;

typedef struct
{
    const char *name;
    int isSolid;
    Vector2 textureIndex;

    void (*onBreak)(void);
    void (*onPlace)(void);
} BlockDefinition;

typedef struct
{
    BlockDefinition registry[256];
    unsigned char blockCount;
} BlockRegistry;

BlockRegistry CreateBlockRegistry();
int RegisterBlock(BlockRegistry *blockRegistry, BlockDefinition blockDefinition);
int InitializeBlockRegistry(BlockRegistry *blockRegistry);

#endif