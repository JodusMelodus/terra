#include "layer.h"

Layer CreateLayer()
{
    Layer layer;
    layer.buffer = malloc(SCREEN_PIXEL_WIDTH * SCREEN_PIXEL_HEIGHT * sizeof(Color));
    if (!layer.buffer)
    {
        perror("Failed to allocate memory for layer buffer");
        exit(1);
    }
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

    if (height > SCREEN_PIXEL_HEIGHT || width > SCREEN_PIXEL_WIDTH)
    {
        printf("LoadLayerTextureFromFile: Texture image too large\nSize: %dx%d\n", width, height);
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

            layer->buffer[(dy + y) * SCREEN_PIXEL_WIDTH + (dx + x)] = (Color){r, g, b, a};
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

    for (size_t y = 0; y < SCREEN_PIXEL_HEIGHT; y++)
        for (size_t x = 0; x < SCREEN_PIXEL_WIDTH; x++)
            layer->buffer[y * SCREEN_PIXEL_WIDTH + x] = color;

    return 0;
}

int DrawLayerBlock(Layer *layer, TextureMap tileMap, const unsigned int x, const unsigned int y, BlockDefinition *blockDefinition)
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

    const int TILE_SIZE = 24;
    int tileStartX = blockDefinition->textureIndex.x * TILE_SIZE;
    int tileStartY = blockDefinition->textureIndex.y * TILE_SIZE;

    for (int dy = 0; dy < TILE_SIZE; dy++)
    {
        for (int dx = 0; dx < TILE_SIZE; dx++)
        {
            int texX = tileStartX + dx;
            int texY = tileStartY + dy;

            if (texX >= tileMap.width || texY >= tileMap.height)
                continue;

            int index = (texY * tileMap.width + texX) * tileMap.channels;
            unsigned char r = tileMap.textureData[index];
            unsigned char g = (tileMap.channels > 1) ? tileMap.textureData[index + 1] : 0;
            unsigned char b = (tileMap.channels > 2) ? tileMap.textureData[index + 2] : 0;
            unsigned char a = (tileMap.channels > 3) ? tileMap.textureData[index + 3] : 255;

            int px = x + dx;
            int py = y + dy;
            if (px < 0 || px >= SCREEN_PIXEL_WIDTH || py < 0 || py >= SCREEN_PIXEL_HEIGHT)
                continue;

            layer->buffer[py * SCREEN_PIXEL_WIDTH + px] = (Color){r, g, b, a};
        }
    }

    return 0;
}

void FreeLayer(Layer *layer)
{
    if (layer && layer->buffer)
    {
        free(layer->buffer);
        layer->buffer = NULL;
    }
}
