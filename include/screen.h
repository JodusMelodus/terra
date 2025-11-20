#ifndef SCREEN_H
#define SCREEN_H

#include "layer.h"

typedef struct
{
    unsigned int width, height;
    unsigned char layerCount;
    Layer **layers;
} ScreenBuffer;

ScreenBuffer *CreateScreenBuffer(const unsigned int width, const unsigned int height);
void FreeScreenBuffer(ScreenBuffer *screen);

#endif