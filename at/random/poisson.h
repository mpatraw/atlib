
#ifndef AT_POISSON_H
#define AT_POISSON_H

#include <stdint.h>

typedef uint32_t at_next_func(void *);

#ifdef __cplusplus
extern "C" {
#endif

unsigned at_next_poisson(at_next_func *f, void *v, double mean);
double at_next_exponential(at_next_func *f, void *v, double lambda);
double at_next_gamma(at_next_func *f, void *v, double alpha, double beta);
double at_next_weibull(at_next_func *f, void *v, double a, double b);
double at_next_extreme_value(at_next_func *f, void *v, double a, double b);

#ifdef __cplusplus
}
#endif

#endif
