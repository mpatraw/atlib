
#ifndef AT_NORMAL_H
#define AT_NORMAL_H

#include <stdint.h>

typedef uint32_t at_next_func(void *);

#ifdef __cplusplus
extern "C" {
#endif

double at_next_normal(at_next_func *f, void *v, double mean, double dev);
double at_next_lognormal(at_next_func *f, void *v, double mean, double dev);
double at_next_chi_squared(at_next_func *f, void *v, double n);
double at_next_cauchy(at_next_func *f, void *v, double median, double dev);
double at_next_fischer_f(at_next_func *f, void *v, double m, double n);

#ifdef __cplusplus
}
#endif

#endif
