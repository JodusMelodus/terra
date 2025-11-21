#include <stdio.h>

#include "raylib.h"
#include "screen.h"
#include "entity.h"

int main()
{
    const unsigned int width = 1700;
    const unsigned int height = 960;

    InitWindow(width, height, "Terra");
    SetTargetFPS(60);

    ScreenBuffer *screen = CreateScreenBuffer(width, height);
    Entity *player = CreateEntity("Player", 50, 50, "../../textures/test.png", 50, 50);
    Image image = {
        .data = screen->layers[BackgroundLayer]->buffer,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    Texture2D texture = LoadTextureFromImage(image);

    float deltaTime = 0;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_A))
            player->xVelocity = -200;
        else if (IsKeyDown(KEY_D))
            player->xVelocity = 200;
        else
            player->xVelocity = 0;

        player->yVelocity += 980.0f * deltaTime;

        if (IsKeyDown(KEY_SPACE) && EntityOnGround(player))
            player->yVelocity = -500;

        if (player->y >= 900.0f)
        {
            player->y = 900.0f;
            if (player->yVelocity > 0)
                player->yVelocity = 0;
        }

        FillLayer(screen->layers[BackgroundLayer], BLACK);
        DrawLayerEntity(screen->layers[BackgroundLayer], player);

        UpdateEntity(player, deltaTime);

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