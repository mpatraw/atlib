
#ifndef AT_NOISE_PERLIN_H
#define AT_NOISE_PERLIN_H

#include "pstdint.h"

struct at_perlin {
	unsigned char _state[256];
};

#ifdef __cplusplus
extern "C" {
#endif

void at_perlin_seed(struct at_perlin *per, uint32_t (*f)(void *), void *v);
double at_perlin_get_2d(struct at_perlin *per, double x, double y);
double at_perlin_get_3d(struct at_perlin *per, double x, double y, double z);
double at_perlin_get_4d(
        struct at_perlin *per, double x, double y, double z, double w);

#ifdef __cplusplus
}
#endif

#endif
