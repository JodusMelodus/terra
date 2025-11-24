#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "screen.h"
#include "block.h"
#include "types.h"
#include "entity.h"
#include "utils.h"

typedef struct
{
    ScreenBuffer screen;
    BlockRegistry blockRegistry;
    Entity player;
    BlockID world[SCREEN_BLOCK_HEIGHT][SCREEN_BLOCK_WIDTH];
    Texture2D textures[3];
} Game;

Game *CreateGame();
int GenerateWorld(Game *game, unsigned int seed);
int RunGame(Game *game);
int DrawWorld(Game *game);
void FinishGame(Game *game);

#endif