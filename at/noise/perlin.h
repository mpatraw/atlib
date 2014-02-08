
#ifndef AT_PERLIN_H
#define AT_PERLIN_H

typedef uint32_t at_next_func(void *);

struct at_perlin
{
        unsigned char _state[256];
};

#ifdef __cplusplus
extern "C" {
#endif

void at_perlin_seed(struct at_perlin *p, at_next_func *f, void *v);
double at_perlin_1(struct at_perlin *p, double x);
double at_perlin_2(struct at_perlin *p, double x, double y);
double at_perlin_3(struct at_perlin *p, double x, double y, double z);
double at_perlin_4(struct at_perlin *p, double x, double y, double z, double t);

#ifdef __cplusplus
}
#endif

#endif
