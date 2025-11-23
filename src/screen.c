#include "screen.h"

ScreenBuffer CreateScreenBuffer()
{
    ScreenBuffer screen;

    for (size_t i = 0; i < 3; i++)
        screen.layers[i] = CreateLayer();

    screen.tileMap = CreateTextureMap("../../textures/tilemap.png");
    return screen;
}

void FreeScreenBuffer(ScreenBuffer *screen)
{
    if (!screen)
        return;
    stbi_image_free(screen->tileMap.textureData);

    for (size_t i = 0; i < 3; i++)
    {
        FreeLayer(&screen->layers[i]);
    }
}
