#include "game.h"

Game *CreateGame()
{
    Game *game = malloc(sizeof(Game));
    if (!game)
    {
        printf("CreateGame: Failed to allocate memory for game\n");
        return NULL;
    }

    ScreenBuffer *screen = CreateScreenBuffer(SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT);
    if (!screen)
    {
        printf("CreateGame: Failed to create screen\n");
        return NULL;
    }

    BlockRegistry *blockRegistry = CreateBlockRegistry();
    if (!blockRegistry)
    {
        printf("CreateGame: Failed to create block registry\n");
        return NULL;
    }

    Entity *player = CreateEntity("Player", 50, 50, "../../textures/test.png", 50, 50);
    if (!player)
    {
        printf("CreateGame: Failed to create player entity\n");
        return NULL;
    }

    game->screen = screen;
    game->blockRegistry = blockRegistry;
    game->player = player;

    InitializeBlockRegistry(game->blockRegistry);

    game->world[0][0] = BI_Grass;

    InitWindow(SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT, "Terra");

    Image backgroundImage = {
        .data = game->screen->layers[BackgroundLayer]->buffer,
        .width = SCREEN_PIXEL_WIDTH,
        .height = SCREEN_PIXEL_HEIGHT,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    game->textures[BackgroundLayer] = LoadTextureFromImage(backgroundImage);

    LoadLayerTextureFromFile(game->screen->layers[BackgroundLayer], 0, 0, "../../textures/background.png");
    UpdateTexture(game->textures[BackgroundLayer], game->screen->layers[BackgroundLayer]->buffer);

    Image midgroundImage = {
        .data = game->screen->layers[MidgroundLayer]->buffer,
        .width = SCREEN_PIXEL_WIDTH,
        .height = SCREEN_PIXEL_HEIGHT,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1};

    game->textures[MidgroundLayer] = LoadTextureFromImage(midgroundImage);

    return game;
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

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_A))
            game->player->velocity.x = -200;
        else if (IsKeyDown(KEY_D))
            game->player->velocity.x = 200;
        else
            game->player->velocity.x = 0;

        game->player->velocity.y += 980.0f * deltaTime;

        if (IsKeyDown(KEY_SPACE) && EntityOnGround(game->player))
            game->player->velocity.y = -500;

        if (game->player->y >= 900.0f)
        {
            game->player->y = 900.0f;
            if (game->player->velocity.y > 0)
                game->player->velocity.y = 0;
        }

        FillLayer(game->screen->layers[MidgroundLayer], BLANK);
        UpdateEntity(game->player, deltaTime);
        DrawLayerEntity(game->screen->layers[MidgroundLayer], game->player);

        UpdateTexture(game->textures[MidgroundLayer], game->screen->layers[MidgroundLayer]->buffer);
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
            BlockID blockId = game->world[x][y];
            BlockDefinition *blockDefinition = &game->blockRegistry->registry[blockId];
            DrawLayerBlock(game->screen->layers[MidgroundLayer], x * 24, y * 24, blockDefinition);
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

    free(game->blockRegistry);
    free(game->player);

    FreeScreenBuffer(game->screen);
    UnloadTexture(game->textures[BackgroundLayer]);
    UnloadTexture(game->textures[MidgroundLayer]);
    CloseWindow();
}
