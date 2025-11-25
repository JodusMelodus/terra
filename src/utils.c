#include "utils.h"

void noiseSeed(unsigned int seed)
{
    noise[0] = (float)(seed % 10) / 7.3;
    noise[1] = (float)(seed % 6) / 12.3;
    noise[2] = (float)(seed % 8) / 5.32;
    noise[3] = (float)(seed % 2) / 5.75;
    noise[4] = (float)(seed % 9) / 6.54;
}

float sigmoid(float x)
{
    return 1.0 / (1.0 + expf(-x)) - 0.5;
}

float noiseGet(float x)
{
    return sigmoid(sinf(noise[0] * x) + sinf(noise[1] * x) + sinf(noise[2] * x) + sinf(noise[3] * x) + sinf(noise[4] * x));
}
