
/**
 * normal distribution functions, requires poisson distribution
 */
#ifndef AT_NORMAL_H
#define AT_NORMAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

double at_next_normal(uint32_t (*f)(void *), void *v, double mean, double dev);
double at_next_lognormal(
        uint32_t (*f)(void *), void *v, double mean, double dev);
double at_next_chi_squared(uint32_t (*f)(void *), void *v, double n);
double at_next_cauchy(
        uint32_t (*f)(void *), void *v, double median, double dev);
double at_next_fischer_f(uint32_t (*f)(void *), void *v, double m, double n);

#ifdef __cplusplus
}
#endif

#endif
