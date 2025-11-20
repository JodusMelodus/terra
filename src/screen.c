#include "screen.h"

ScreenBuffer *CreateScreenBuffer(const unsigned int width, const unsigned int height)
{
    ScreenBuffer *screen = malloc(sizeof(ScreenBuffer));
    if (!screen)
        return NULL;

    Layer *layer = CreateLayer(width, height);
    if (!layer)
    {
        free(screen);
        return NULL;
    }

    screen->layerCount = 1;
    screen->width = width;
    screen->height = height;

    screen->layers = malloc(sizeof(Layer *));
    if (!screen->layers)
    {
        FreeLayer(layer);
        free(screen);
        return NULL;
    }

    screen->layers[0] = layer;
    return screen;
}

void FreeScreenBuffer(ScreenBuffer *screen)
{
    if (!screen)
        return;
    for (size_t i = 0; i < screen->layerCount; i++)
        FreeLayer(screen->layers[i]);
    free(screen->layers);
    free(screen);
}
