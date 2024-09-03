#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

static uint32_t seed = 1;

#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 0xFFFFFFFF

void srand(uint32_t s);
uint32_t rand();
int rand_range(int min, int max);

#endif