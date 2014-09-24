
/**
 * poisson distribution functions
 */
#ifndef AT_RANDOM_POISSON_H
#define AT_RANDOM_POISSON_H

#include "pstdint.h"

#ifdef __cplusplus
extern "C" {
#endif


unsigned at_get_next_poisson(double mean, uint32_t (*f)(void *), void *v);
double at_get_next_exponential(double lambda, uint32_t (*f)(void *), void *v);
double at_get_next_gamma(
        double alpha, double beta, uint32_t (*f)(void *), void *v);
double at_get_next_weibull(double a, double b, uint32_t (*f)(void *), void *v);
double at_get_next_extreme_value(
        double a, double b, uint32_t (*f)(void *), void *v);

#ifdef __cplusplus
}
#endif

#endif
