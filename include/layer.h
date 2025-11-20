#ifndef LAYER_H
#define LAYER_H

#include <stdlib.h>
#include "types.h"
#include "raylib.h"

typedef struct
{
    unsigned int width, height;
    Color *buffer;
} Layer;

#endif