#include <stdio.h>

#include "raylib.h"
#include "screen.h"

int main()
{
    const unsigned int width = 1700;
    const unsigned int height = 960;

    InitWindow(width, height, "Terra");
    SetTargetFPS(60);

    ScreenBuffer *screen = CreateScreenBuffer(width, height);

    Image image = {
        .data = screen->layers[BackgroundLayer]->buffer,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    Texture2D texture = LoadTextureFromImage(image);

    unsigned int x = 0;
    unsigned int y = 0;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_A))
            x -= 1;
        if (IsKeyDown(KEY_D))
            x += 1;
        if (IsKeyDown(KEY_W))
            y -= 1;
        if (IsKeyDown(KEY_S))
            y += 1;

        LoadLayerTextureFromFile(screen->layers[BackgroundLayer], x, y, "../../textures/test.png");
        // LoadLayerTextureFromFile(screen->layers[BackgroundLayer], x + 50, y + 50, "../../textures/test.png");

        UpdateTexture(texture, screen->layers[BackgroundLayer]->buffer);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(texture, 0, 0, WHITE);
        EndDrawing();
    }

    FreeScreenBuffer(screen);
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}