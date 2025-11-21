#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    const char *name;
    const char *texture;
    int width, height;
    float x, y, xVelocity, yVelocity;
} Entity;

Entity *CreateEntity(const char *name, float x, float y, const char *texture, int width, int height);
int EntityOnGround(Entity *entity);
void UpdateEntity(Entity *entity, float deltaTime);

#endif