#include "../libc/include/random.h"

void srand(uint32_t s) {
    seed = s;
}

uint32_t rand() {
    seed = (LCG_A * seed + LCG_C) & LCG_M;
    return seed;
}

int rand_range(int min, int max) {
    uint32_t random = rand();
    return min + (random % (max - min + 1));
}