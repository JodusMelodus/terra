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
    Texture2D textures[3];
    Vector2 camera;
};

struct Game *CreateGame(unsigned int seed);
enum BlockID GetWorldBlock(struct Game *game, int height);
int RunGame(struct Game *game);
void HandlePlayerMovement(struct Game *game);
int DrawWorld(struct Game *game);
void RedrawGame(struct Game *game);
void FinishGame(struct Game *game);

#endif