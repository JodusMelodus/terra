#include "block.h"

BlockRegistry CreateBlockRegistry()
{
    return (BlockRegistry){
        .blockCount = 0,
        .registry = {0}};
}

int RegisterBlock(BlockRegistry *blockRegistry, BlockDefinition blockDefinition)
{
    if (!blockRegistry)
    {
        printf("RegisterBlock: Invalid block registry pointer\n");
        return 1;
    }

    blockRegistry->registry[blockRegistry->blockCount++] = blockDefinition;
    return 0;
}

int InitializeBlockRegistry(BlockRegistry *blockRegistry)
{
    if (!blockRegistry)
    {
        printf("InitializeBlockRegistry: Invalid block registry pointer\n");
        return 1;
    }

    RegisterBlock(blockRegistry, (BlockDefinition){.name = "Air", .isSolid = 0, .textureIndex = (Vector2){3, 0}, .onBreak = NULL, .onPlace = NULL});
    RegisterBlock(blockRegistry, (BlockDefinition){.name = "Dirt", .isSolid = 1, .textureIndex = (Vector2){1, 0}, .onBreak = NULL, .onPlace = NULL});
    RegisterBlock(blockRegistry, (BlockDefinition){.name = "Grass", .isSolid = 1, .textureIndex = (Vector2){0, 0}, .onBreak = NULL, .onPlace = NULL});
    RegisterBlock(blockRegistry, (BlockDefinition){.name = "Stone", .isSolid = 1, .textureIndex = (Vector2){2, 0}, .onBreak = NULL, .onPlace = NULL});

    return 0;
}
