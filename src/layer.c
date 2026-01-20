#include "layer.h"

struct Layer CreateLayer()
{
    struct Layer layer;
    layer.buffer = malloc(SCREEN_PIXEL_WIDTH * SCREEN_PIXEL_HEIGHT * sizeof(Color));
    if (!layer.buffer)
    {
        perror("Failed to allocate memory for layer buffer");
        exit(1);
    }
    return layer;
}

int LoadLayerTextureFromFile(struct Layer *layer, int x, int y, const char *texturePath)
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

            int py = dy + y;
            int px = dx + x;
            if (py >= 0 && py < SCREEN_PIXEL_HEIGHT && px >= 0 && px < SCREEN_PIXEL_WIDTH)
            {
                int i = py * SCREEN_PIXEL_WIDTH + px;
                layer->buffer[i] = (Color){r, g, b, a};
            }
        }
    }

    stbi_image_free(textureData);
    return 0;
}

int DrawLayerEntity(struct Layer *layer, struct Entity *entity, Vector2 camera)
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

    int drawX = (int)(entity->position.x - camera.x);
    int drawY = (int)(entity->position.y - camera.y);
    return LoadLayerTextureFromFile(layer, drawX, drawY, entity->texture);
}

int FillLayer(struct Layer *layer, Color color)
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

int DrawLayerBlock(struct Layer *layer, struct TextureMap tileMap, const unsigned int x, const unsigned int y, struct BlockDefinition *blockDefinition)
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

    int tileStartX = blockDefinition->textureIndex.x * BLOCK_SIZE;
    int tileStartY = blockDefinition->textureIndex.y * BLOCK_SIZE;

    for (int dy = 0; dy < BLOCK_SIZE; dy++)
    {
        for (int dx = 0; dx < BLOCK_SIZE; dx++)
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

void FreeLayer(struct Layer *layer)
{
    if (layer && layer->buffer)
    {
        free(layer->buffer);
        layer->buffer = NULL;
    }
}
