#ifndef LAYER_H
#define LAYER_H

#include <stdlib.h>
#include <raylib.h>
#include <stb_image.h>

#include "types.h"
#include "entity.h"

typedef struct
{
    unsigned int width, height;
    Color *buffer;
} Layer;

Layer *CreateLayer(const unsigned int width, const unsigned int height);
int LoadLayerTextureFromFile(Layer *layer, const unsigned int x, const unsigned int y, const char *texturePath);
int DrawLayerEntity(Layer *layer, Entity *entity);
int FillLayer(Layer *layer, Color color);
void FreeLayer(Layer *layer);

#endif