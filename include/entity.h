#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "types.h"

struct Entity
{
    const char *name;
    const char *texture;
    int x, y;
    Vector2 velocity;
};

struct Entity CreateEntity(const char *name, int x, int y, const char *texture);
int EntityOnGround(struct Entity *entity);
void UpdateEntity(struct Entity *entity, float deltaTime);

#endif