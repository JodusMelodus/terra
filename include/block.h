#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <stdio.h>

typedef enum
{
    BI_Dirt,
    BI_Grass
} BlockID;

typedef struct
{
    const char *name;
    int isSolid;
    int textureIndex;

    void (*onBreak)(void);
    void (*onPlace)(void);
} BlockDefinition;

typedef struct
{
    BlockDefinition registry[256];
    unsigned char blockCount;
} BlockRegistry;

BlockRegistry *CreateBlockRegistry();
int RegisterBlock(BlockRegistry *blockRegistry, BlockDefinition blockDefinition);
int InitializeBlockRegistry(BlockRegistry *blockRegistry);

#endif