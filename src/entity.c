#include "entity.h"

struct Entity CreateEntity(const char *name, const char *texture)
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
        .position = (Vector2){SCREEN_PIXEL_WIDTH / 2.0f, GROUND_LEVEL},
        .velocity = (Vector2){0, 0},
        .grounded = 1,
    };
}