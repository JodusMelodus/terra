#include "entity.h"

struct Entity CreateEntity(const char *name, int x, int y, const char *texture)
{
    if (!name)
    {
        printf("CreateEntity: Invalid name pointer\n");
        exit(1);
    }

    if (!texture)
    {
        printf("CreateEntity: Invalid texture pointer\n");
        exit(1);
    }

    return (struct Entity){
        .name = name,
        .texture = texture,
        .velocity = {0, 0},
        .x = x,
        .y = y};
}

int EntityOnGround(struct Entity *entity)
{
    if (!entity)
    {
        printf("EntityOnGround: Invalid entity pointer\n");
        return 1;
    }

    return entity->y >= GROUND_LEVEL;
}

void UpdateEntity(struct Entity *entity, float deltaTime)
{
    entity->x += round(entity->velocity.x * deltaTime);
    entity->y += round(entity->velocity.y * deltaTime);
}
