
#ifndef AT_UNIFORM_H
#define AT_UNIFORM_H

#include <stdint.h>

typedef uint32_t at_next_func(void *);

#ifdef __cplusplus
extern "C" {
#endif

int32_t at_uniform_i(at_next_func *f, void *v, int32_t l, int32_t u);
double at_uniform_d(at_next_func *f, void *v, double l, double u);

#ifdef __cplusplus
}
#endif

#endif
