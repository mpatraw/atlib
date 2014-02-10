
/**
 * poisson distribution functions
 */
#ifndef AT_POISSON_H
#define AT_POISSON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


unsigned at_get_next_poisson(uint32_t (*f)(void *), void *v, double mean);
double at_get_next_exponential(uint32_t (*f)(void *), void *v, double lambda);
double at_get_next_gamma(
        uint32_t (*f)(void *), void *v, double alpha, double beta);
double at_get_next_weibull(uint32_t (*f)(void *), void *v, double a, double b);
double at_get_next_extreme_value(
        uint32_t (*f)(void *), void *v, double a, double b);

#ifdef __cplusplus
}
#endif

#endif
