#include <stdio.h>

#include "raylib.h"
#include "screen.h"
#include "entity.h"

int main()
{
    const unsigned int width = 1700;
    const unsigned int height = 950;

    InitWindow(width, height, "Terra");
    SetTargetFPS(60);

    ScreenBuffer *screen = CreateScreenBuffer(width, height);
    Entity *player = CreateEntity("Player", 50, 50, "../../textures/test.png", 50, 50);
    Image backgroundImage = {
        .data = screen->layers[BackgroundLayer]->buffer,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    Texture2D textureBackground = LoadTextureFromImage(backgroundImage);

    Image midgroundImage = {
        .data = screen->layers[MidgroundLayer]->buffer,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    Texture2D textureMidground = LoadTextureFromImage(midgroundImage);

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

        LoadLayerTextureFromFile(screen->layers[BackgroundLayer], 0, 0, "../../textures/background.png");

        Color c = {0, 0, 0, 0};
        FillLayer(screen->layers[MidgroundLayer], c);
        UpdateEntity(player, deltaTime);
        DrawLayerEntity(screen->layers[MidgroundLayer], player);

        UpdateTexture(textureBackground, screen->layers[BackgroundLayer]->buffer);
        UpdateTexture(textureMidground, screen->layers[MidgroundLayer]->buffer);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(textureBackground, 0, 0, WHITE);
        DrawTexture(textureMidground, 0, 0, WHITE);
        EndDrawing();
    }

    FreeScreenBuffer(screen);
    UnloadTexture(textureBackground);
    UnloadTexture(textureMidground);
    CloseWindow();
    return 0;
}