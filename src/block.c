#include "block.h"

BlockRegistry *CreateBlockRegistry()
{
    BlockRegistry *blockRegistry = malloc(sizeof(BlockRegistry));
    if (!blockRegistry)
    {
        printf("CreateBlockRegistry: Failed to allocate memory for block registry\n");
        return NULL;
    }

    blockRegistry->blockCount = 0;
    return blockRegistry;
}

int RegisterBlock(BlockRegistry *blockRegistry, BlockDefinition blockDefinition)
{
    if (!blockRegistry)
    {
        printf("RegisterBlock: Invalid block registry pointer\n");
        return 1;
    }

    blockRegistry->registry[blockRegistry->blockCount] = blockDefinition;
    return 0;
}

int InitializeBlockRegistry(BlockRegistry *blockRegistry)
{
    if (!blockRegistry)
    {
        printf("InitializeBlockRegistry: Invalid block registry pointer\n");
        return NULL;
    }

    RegisterBlock(blockRegistry, (BlockDefinition){
                                     .name = "Dirt",
                                     .isSolid = 1,
                                     .textureIndex = 0});

    RegisterBlock(blockRegistry, (BlockDefinition){
                                     .name = "Grass",
                                     .isSolid = 1,
                                     .textureIndex = 1});

    return 0;
}
