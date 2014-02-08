
#ifndef AT_PERLIN_H
#define AT_PERLIN_H

#include <stdint.h>

typedef uint32_t at_next_func(void *);

struct at_perlin
{
        unsigned char _state[256];
};

#ifdef __cplusplus
extern "C" {
#endif

void at_perlin_seed(struct at_perlin *p, at_next_func *f, void *v);
double at_perlin_1d(struct at_perlin *p, double x);
double at_perlin_2d(struct at_perlin *p, double x, double y);
double at_perlin_3d(struct at_perlin *p, double x, double y, double z);

#ifdef __cplusplus
}
#endif

#endif
