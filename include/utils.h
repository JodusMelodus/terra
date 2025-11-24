#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

static float noise[5];

void noiseSeed(unsigned int seed);
float sigmoid(float x);
float noiseGet(float x);

#endif