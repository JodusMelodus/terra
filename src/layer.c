#include "layer.h"

Layer *CreateLayer(const unsigned int width, const unsigned int height)
{
    Layer *layer = malloc(sizeof(Layer));
    if (!layer)
        return NULL;

    layer->buffer = calloc(width * height, sizeof(Color));
    if (!layer->buffer)
    {
        free(layer);
        return NULL;
    }
    
    layer->height = height;
    layer->width = width;
    return layer;
}

void FreeLayer(Layer *layer)
{
    if (!layer)
        return;
    free(layer->buffer);
    free(layer);
}
