#include "game.h"

struct Game *CreateGame()
{
    struct Game *game = malloc(sizeof(struct Game));
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

    Image foregroundImage = {
        .data = game->screen.layers[ForegroundLayer].buffer,
        .width = SCREEN_PIXEL_WIDTH,
        .height = SCREEN_PIXEL_HEIGHT,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    game->textures[ForegroundLayer] = LoadTextureFromImage(foregroundImage);

    return game;
}

int GenerateWorld(struct Game *game, unsigned int seed)
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

int RunGame(struct Game *game)
{
    if (!game)
    {
        printf("RunGame: Invalid game pointer\n");
        return 1;
    }

    SetTargetFPS(60);
    surroundingBlocks[Down] = game->blockRegistry.registry[BI_Air];

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        mousePosition = GetMousePosition();
        HandlePlayerMovement(game);
        RedrawGame(game);
    }

    return 0;
}

void HandlePlayerMovement(struct Game *game)
{
    int x = game->player.x / BLOCK_SIZE;
    int y = game->player.y / BLOCK_SIZE;

    if (x < 0)
        x = 0;
    if (x >= SCREEN_BLOCK_WIDTH)
        x = SCREEN_BLOCK_WIDTH - 1;
    if (y < 0)
        y = 0;
    if (y >= SCREEN_BLOCK_HEIGHT)
        y = SCREEN_BLOCK_HEIGHT - 1;

    surroundingBlocks[Up] = (y == 0) ? game->blockRegistry.registry[BI_Air] : game->blockRegistry.registry[game->world[y - 1][x]];
    surroundingBlocks[Down] = (y == SCREEN_BLOCK_HEIGHT - 1) ? game->blockRegistry.registry[BI_Air] : game->blockRegistry.registry[game->world[y + 1][x]];
    surroundingBlocks[Left] = (x == 0) ? game->blockRegistry.registry[BI_Air] : game->blockRegistry.registry[game->world[y][x - 1]];
    surroundingBlocks[Right] = (x == SCREEN_BLOCK_WIDTH - 1) ? game->blockRegistry.registry[BI_Air] : game->blockRegistry.registry[game->world[y][x + 1]];

    if (IsKeyDown(KEY_A) && !surroundingBlocks[Left].isSolid)
        game->player.velocity.x = -200;
    else if (IsKeyDown(KEY_D) && !surroundingBlocks[Right].isSolid)
        game->player.velocity.x = 200;
    else
        game->player.velocity.x = 0;

    if (IsKeyDown(KEY_SPACE) && surroundingBlocks[Down].isSolid && !surroundingBlocks[Up].isSolid)
        game->player.velocity.y = -250;

    if (surroundingBlocks[Down].isSolid)
    {
        groundLevel = (y + 1) * BLOCK_SIZE - BLOCK_SIZE / 2;
        if (game->player.y > groundLevel)
        {
            game->player.y = groundLevel;
            if (game->player.velocity.y > 0)
                game->player.velocity.y = 0;
        }
    }
    else
    {
        game->player.velocity.y += 1000.0f * deltaTime;
        groundLevel = SCREEN_PIXEL_HEIGHT - BLOCK_SIZE / 2;
    }
    game->player.y += game->player.velocity.y * deltaTime;
}

int DrawWorld(struct Game *game)
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
            enum BlockID blockId = game->world[y][x];
            struct BlockDefinition *blockDefinition = &game->blockRegistry.registry[blockId];
            DrawLayerBlock(&game->screen.layers[MidgroundLayer], game->screen.tileMap, x * BLOCK_SIZE, y * BLOCK_SIZE, blockDefinition);
        }
    }

    return 0;
}

void RedrawGame(struct Game *game)
{
    FillLayer(&game->screen.layers[MidgroundLayer], BLANK);
    FillLayer(&game->screen.layers[ForegroundLayer], BLANK);
    DrawWorld(game);
    UpdateEntity(&game->player, deltaTime);
    DrawLayerEntity(&game->screen.layers[MidgroundLayer], &game->player);
    LoadLayerTextureFromFile(
        &game->screen.layers[ForegroundLayer],
        (int)(mousePosition.x / BLOCK_SIZE) * BLOCK_SIZE,
        (int)(mousePosition.y / BLOCK_SIZE) * BLOCK_SIZE,
        "../../textures/mouse.png");

    UpdateTexture(game->textures[MidgroundLayer], game->screen.layers[MidgroundLayer].buffer);
    UpdateTexture(game->textures[ForegroundLayer], game->screen.layers[ForegroundLayer].buffer);
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(game->textures[BackgroundLayer], 0, 0, WHITE);
    DrawTexture(game->textures[MidgroundLayer], 0, 0, WHITE);
    DrawTexture(game->textures[ForegroundLayer], 0, 0, WHITE);
    EndDrawing();
}

void FinishGame(struct Game *game)
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
