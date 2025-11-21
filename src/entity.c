#include "entity.h"

Entity *CreateEntity(const char *name, int x, int y, const char *texture, int width, int height)
{
    Entity *entity = malloc(sizeof(Entity));
    if (!entity)
    {
        printf("CreateEntity: Failed to allocate memory for entity\n");
        return NULL;
    }

    if (!name)
    {
        printf("CreateEntity: Invalid name pointer\n");
        return NULL;
    }

    if (!texture)
    {
        printf("CreateEntity: Invalid texture pointer\n");
        return NULL;
    }

    Vector2 velocity = {.x = 0, .y = 0};

    entity->name = name;
    entity->texture = texture;
    entity->width = width;
    entity->height = height;
    entity->x = x;
    entity->y = y;
    entity->velocity = velocity;
    return entity;
}

int EntityOnGround(Entity *entity)
{
    if (!entity)
    {
        printf("EntityOnGround: Invalid entity pointer\n");
        return 0;
    }

    return entity->y >= 900.0f;
}

void UpdateEntity(Entity *entity, float deltaTime)
{
    entity->x += round(entity->velocity.x * deltaTime);
    entity->y += round(entity->velocity.y * deltaTime);
}
