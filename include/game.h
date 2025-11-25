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

static float deltaTime = 0;
static int groundLevel = GROUND_LEVEL;
static Vector2 mousePosition;
static struct BlockDefinition surroundingBlocks[4];

struct Game
{
    struct ScreenBuffer screen;
    struct BlockRegistry blockRegistry;
    struct Entity player;
    enum BlockID world[SCREEN_BLOCK_HEIGHT][SCREEN_BLOCK_WIDTH];
    Texture2D textures[3];
};

struct Game *CreateGame();
int GenerateWorld(struct Game *game, unsigned int seed);
int RunGame(struct Game *game);
void HandlePlayerMovement(struct Game *game);
int DrawWorld(struct Game *game);
void RedrawGame(struct Game *game);
void FinishGame(struct Game *game);

#endif