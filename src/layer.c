#include "layer.h"

Layer *CreateLayer(const unsigned int width, const unsigned int height)
{
    Layer *layer = malloc(sizeof(Layer));
    if (!layer)
    {
        printf("CreateLayer: Failed to allocate memory for layer\n");
        return NULL;
    }

    layer->buffer = calloc(width * height, sizeof(Color));
    if (!layer->buffer)
    {
        free(layer);
        printf("CreateLayer: Failed to allocate memory for layer buffer\n");
        return NULL;
    }

    layer->height = height;
    layer->width = width;
    return layer;
}

int LoadLayerTextureFromFile(Layer *layer, const unsigned int x, const unsigned int y, const char *texturePath)
{
    int width, height, channels;
    unsigned char *textureData = stbi_load(texturePath, &width, &height, &channels, 0);
    if (!textureData)
    {
        printf("LoadLayerTextureFromFile: Failed to read texture\n");
        return 1;
    }

    if (height > layer->height || width > layer->width)
    {
        printf("LoadLayerTextureFromFile: Texture image too large\n");
        stbi_image_free(textureData);
        return 1;
    }

    for (int dy = 0; dy < height; dy++)
    {
        for (int dx = 0; dx < width; dx++)
        {
            int index = (dy * width + dx) * channels;
            unsigned char r = textureData[index];
            unsigned char g = (channels > 1) ? textureData[index + 1] : 0;
            unsigned char b = (channels > 2) ? textureData[index + 2] : 0;
            unsigned char a = (channels > 3) ? textureData[index + 3] : 255;

            layer->buffer[(dy + y) * layer->width + (dx + x)] = (Color){r, g, b, a};
        }
    }

    stbi_image_free(textureData);
    return 0;
}

int DrawLayerEntity(Layer *layer, Entity *entity)
{
    if (!layer)
    {
        printf("DrawLayerEntity: Invalid layer pointer\n");
        return 1;
    }

    if (!entity)
    {
        printf("DrawLayerEntity: Invalid entity pointer\n");
        return 1;
    }

    return LoadLayerTextureFromFile(layer, entity->x - entity->width / 2, entity->y - entity->height / 2, entity->texture);
}

int FillLayer(Layer *layer, Color color)
{
    if (!layer)
    {
        printf("FillLayer: Invalid layer pointer\n");
        return 1;
    }

    if (!layer->buffer)
    {
        printf("FillLayer: Invalid layer buffer pointer\n");
        return 1;
    }

    for (size_t y = 0; y < layer->height; y++)
        for (size_t x = 0; x < layer->width; x++)
            layer->buffer[y * layer->width + x] = color;

    return 0;
}

int DrawLayerBlock(Layer *layer, const unsigned int x, const unsigned int y, BlockDefinition *blockDefinition)
{
    if (!layer)
    {
        printf("DrawLayerBlock: Invalid layer pointer\n");
        return 1;
    }

    if (!blockDefinition)
    {
        printf("DrawLayerBlock: Invalid block definition pointer\n");
        return 1;
    }

    // TODO interpret x and y to get texture from tilemap

    return 0;
}

void FreeLayer(Layer *layer)
{
    if (!layer)
        return;
    free(layer->buffer);
    free(layer);
}
