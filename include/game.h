#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>

#include "screen.h"
#include "block.h"
#include "types.h"
#include "entity.h"

#define SCREEN_WIDTH 1700
#define SCREEN_HEIGHT 950

typedef struct
{
    ScreenBuffer *screen;
    BlockRegistry *blockRegistry;
    Entity *player;
    BlockID world[10][10];
    Texture2D textures[3];
} Game;

Game *CreateGame();
int RunGame(Game *game);
void FinishGame(Game *game);

#endif