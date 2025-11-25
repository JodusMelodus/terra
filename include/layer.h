#ifndef LAYER_H
#define LAYER_H

#include <stdlib.h>
#include <raylib.h>
#include <stb_image.h>

#include "types.h"
#include "entity.h"
#include "block.h"

struct Layer
{
    Color *buffer;
};

struct Layer CreateLayer();
int LoadLayerTextureFromFile(struct Layer *layer, const unsigned int x, const unsigned int y, const char *texturePath);
int DrawLayerEntity(struct Layer *layer, struct Entity *entity);
int FillLayer(struct Layer *layer, Color color);
int DrawLayerBlock(struct Layer *layer, struct TextureMap tileMap, const unsigned int x, const unsigned int y, struct BlockDefinition *blockDefinition);
void FreeLayer(struct Layer *layer);

#endif