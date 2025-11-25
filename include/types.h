#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stb_image.h>

#define SCREEN_PIXEL_WIDTH 1680
#define SCREEN_PIXEL_HEIGHT 960
#define BLOCK_SIZE 48
#define SCREEN_BLOCK_WIDTH (SCREEN_PIXEL_WIDTH / BLOCK_SIZE)
#define SCREEN_BLOCK_HEIGHT (SCREEN_PIXEL_HEIGHT / BLOCK_SIZE)
#define GROUND_LEVEL (SCREEN_PIXEL_HEIGHT - BLOCK_SIZE)

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

enum LayerID
{
    BackgroundLayer,
    ForegroundLayer,
    MidgroundLayer
};

struct TextureMap
{
    int width, height, channels;
    unsigned char *textureData;
};

struct TextureMap CreateTextureMap(const char *path);
void FreeTextureMap(struct TextureMap *textureMap);

#endif