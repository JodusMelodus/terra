#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>

#include "screen.h"
#include "block.h"
#include "types.h"
#include "entity.h"

#define SCREEN_PIXEL_WIDTH 1680
#define SCREEN_PIXEL_HEIGHT 960
#define SCREEN_BLOCK_WIDTH SCREEN_PIXEL_WIDTH / 24
#define SCREEN_BLOCK_HEIGHT SCREEN_PIXEL_HEIGHT / 24

typedef struct
{
    ScreenBuffer *screen;
    BlockRegistry *blockRegistry;
    Entity *player;
    BlockID world[SCREEN_BLOCK_WIDTH][SCREEN_BLOCK_HEIGHT];
    Texture2D textures[3];
} Game;

Game *CreateGame();
int RunGame(Game *game);
int DrawWorld(Game *game);
void FinishGame(Game *game);

#endif