#include "block.h"

struct BlockRegistry CreateBlockRegistry()
{
    return (struct BlockRegistry){
        .blockCount = 0,
        .registry = {0}};
}

int RegisterBlock(struct BlockRegistry *blockRegistry, struct BlockDefinition blockDefinition)
{
    if (!blockRegistry)
    {
        printf("RegisterBlock: Invalid block registry pointer\n");
        return 1;
    }

    blockRegistry->registry[blockRegistry->blockCount++] = blockDefinition;
    return 0;
}

int InitializeBlockRegistry(struct BlockRegistry *blockRegistry)
{
    if (!blockRegistry)
    {
        printf("InitializeBlockRegistry: Invalid block registry pointer\n");
        return 1;
    }

    RegisterBlock(blockRegistry, (struct BlockDefinition){.name = "Air", .isSolid = 0, .textureIndex = (Vector2){3, 0}, .onBreak = NULL, .onPlace = NULL});
    RegisterBlock(blockRegistry, (struct BlockDefinition){.name = "Dirt", .isSolid = 1, .textureIndex = (Vector2){1, 0}, .onBreak = NULL, .onPlace = NULL});
    RegisterBlock(blockRegistry, (struct BlockDefinition){.name = "Grass", .isSolid = 1, .textureIndex = (Vector2){0, 0}, .onBreak = NULL, .onPlace = NULL});
    RegisterBlock(blockRegistry, (struct BlockDefinition){.name = "Stone", .isSolid = 1, .textureIndex = (Vector2){2, 0}, .onBreak = NULL, .onPlace = NULL});

    return 0;
}
