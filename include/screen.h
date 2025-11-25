#ifndef SCREEN_H
#define SCREEN_H

#include "layer.h"
#include "types.h"

struct ScreenBuffer
{
    struct Layer layers[3];
    struct TextureMap tileMap;
};

struct ScreenBuffer CreateScreenBuffer();
void FreeScreenBuffer(struct ScreenBuffer *screen);

#endif