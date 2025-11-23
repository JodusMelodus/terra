#include "game.h"

Game *CreateGame()
{
    Game *game = malloc(sizeof(Game));
    if (!game)
    {
        printf("CreateGame: Failed to allocate memory for game\n");
        return NULL;
    }

    ScreenBuffer *screen = CreateScreenBuffer(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!screen)
    {
        printf("CreateGame: Failed to allocate memory for screen\n");
        return NULL;
    }

    BlockRegistry *blockRegistry = CreateBlockRegistry();
    if (!blockRegistry)
    {
        printf("CreateGame: Failed to allocate memory for block registry\n");
        return NULL;
    }

    game->screen = screen;
    game->blockRegistry = blockRegistry;

    InitializeBlockRegistry(game->blockRegistry);

    return game;
}