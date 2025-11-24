#include "game.h"

Game *CreateGame()
{
    Game *game = malloc(sizeof(Game));
    if (!game)
    {
        perror("Failed to allocate memory for game");
        return NULL;
    }

    game->screen = CreateScreenBuffer();
    game->blockRegistry = CreateBlockRegistry();
    game->player = CreateEntity("Player", 50, 50, "../../textures/test.png");

    InitializeBlockRegistry(&game->blockRegistry);

    for (size_t y = 0; y < SCREEN_BLOCK_HEIGHT; y++)
        for (size_t x = 0; x < SCREEN_BLOCK_WIDTH; x++)
            game->world[y][x] = BI_Air;

    InitWindow(SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT, "Terra");

    Image backgroundImage = {
        .data = game->screen.layers[BackgroundLayer].buffer,
        .width = SCREEN_PIXEL_WIDTH,
        .height = SCREEN_PIXEL_HEIGHT,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    game->textures[BackgroundLayer] = LoadTextureFromImage(backgroundImage);

    LoadLayerTextureFromFile(&game->screen.layers[BackgroundLayer], 0, 0, "../../textures/background.png");
    UpdateTexture(game->textures[BackgroundLayer], game->screen.layers[BackgroundLayer].buffer);

    Image midgroundImage = {
        .data = game->screen.layers[MidgroundLayer].buffer,
        .width = SCREEN_PIXEL_WIDTH,
        .height = SCREEN_PIXEL_HEIGHT,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    game->textures[MidgroundLayer] = LoadTextureFromImage(midgroundImage);

    return game;
}

int GenerateWorld(Game *game, unsigned int seed)
{
    noiseSeed(seed);

    for (int x = 0; x < SCREEN_BLOCK_WIDTH; x++)
    {
        float y = noiseGet(x / 10.0);
        int height = y * SCREEN_BLOCK_HEIGHT + SCREEN_BLOCK_HEIGHT / 2;
        game->world[height][x] = BI_Grass;
        for (int j = height + 1; j < SCREEN_BLOCK_HEIGHT; j++)
        {
            if (j - height > 3)
                game->world[j][x] = BI_Stone;
            else
                game->world[j][x] = BI_Dirt;
        }
    }

    return 0;
}

int RunGame(Game *game)
{
    if (!game)
    {
        printf("RunGame: Invalid game pointer\n");
        return 1;
    }

    SetTargetFPS(60);
    float deltaTime = 0;
    BlockDefinition blockBeneathMaFeet = game->blockRegistry.registry[BI_Air];
    int groundLevel = GROUND_LEVEL;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_A))
            game->player.velocity.x = -200;
        else if (IsKeyDown(KEY_D))
            game->player.velocity.x = 200;
        else
            game->player.velocity.x = 0;

        game->player.velocity.y += 980.0f * deltaTime;

        if (IsKeyDown(KEY_SPACE) && blockBeneathMaFeet.isSolid)
            game->player.velocity.y = -250;

        if (game->player.y >= groundLevel)
        {
            game->player.y = groundLevel;
            if (game->player.velocity.y > 0)
                game->player.velocity.y = 0;
        }

        int y = (game->player.y / BLOCK_SIZE);
        int x = (game->player.x / BLOCK_SIZE);

        if (blockBeneathMaFeet.isSolid)
            groundLevel = y * BLOCK_SIZE;
        else
            groundLevel = SCREEN_PIXEL_HEIGHT;

        if (y == SCREEN_BLOCK_HEIGHT)
            blockBeneathMaFeet = game->blockRegistry.registry[BI_Air];
        else
            blockBeneathMaFeet = game->blockRegistry.registry[game->world[y][x]];

        FillLayer(&game->screen.layers[MidgroundLayer], BLANK);
        DrawWorld(game);
        UpdateEntity(&game->player, deltaTime);
        DrawLayerEntity(&game->screen.layers[MidgroundLayer], &game->player);

        UpdateTexture(game->textures[MidgroundLayer], game->screen.layers[MidgroundLayer].buffer);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(game->textures[BackgroundLayer], 0, 0, WHITE);
        DrawTexture(game->textures[MidgroundLayer], 0, 0, WHITE);
        EndDrawing();
    }

    return 0;
}

int DrawWorld(Game *game)
{
    if (!game)
    {
        printf("DrawWorld: Invalid game pointer\n");
        return 1;
    }

    for (size_t y = 0; y < SCREEN_BLOCK_HEIGHT; y++)
    {
        for (size_t x = 0; x < SCREEN_BLOCK_WIDTH; x++)
        {
            BlockID blockId = game->world[y][x];
            BlockDefinition *blockDefinition = &game->blockRegistry.registry[blockId];
            DrawLayerBlock(&game->screen.layers[MidgroundLayer], game->screen.tileMap, x * BLOCK_SIZE, y * BLOCK_SIZE, blockDefinition);
        }
    }

    return 0;
}

void FinishGame(Game *game)
{
    if (!game)
    {
        printf("FinishGame: Invalid game pointer\n");
        return;
    }

    UnloadTexture(game->textures[BackgroundLayer]);
    UnloadTexture(game->textures[MidgroundLayer]);
    CloseWindow();
}
