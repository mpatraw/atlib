
#ifndef AT_SAMPLING_H
#define AT_SAMPLING_H

#include <stdint.h>

typedef uint32_t at_next_func(void *);

#ifdef __cplusplus
extern "C" {
#endif

unsigned at_next_discrete(at_next_func *f, void *v, double *w, unsigned l);
double at_next_piecewise_constant(
        at_next_func *f, void *v, double *w, double *b, double l);
double at_next_piecewise_linear(
        at_next_func *f, void *v, double *w, double *b, double *t, double l);

#ifdef __cplusplus
}
#endif

#endif
