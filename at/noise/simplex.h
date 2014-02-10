
#ifndef AT_SIMPLEX_H
#define AT_SIMPLEX_H

#include <stdint.h>

struct at_simplex
{
        unsigned char _p[512];
};

#ifdef __cplusplus
extern "C" {
#endif

void at_simplex_seed(struct at_simplex *sim, uint32_t (*f)(void *), void *v);
double at_simplex_get_2d(struct at_simplex *sim, double x, double y);
double at_simplex_get_3d(struct at_simplex *sim, double x, double y, double z);
double at_simplex_get_4d(struct at_simplex *sim,
        double x, double y, double z, double w);

#ifdef __cplusplus
}
#endif

#endif
