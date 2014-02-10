
/**
 * normal distribution functions, requires poisson distribution
 */
#ifndef AT_NORMAL_H
#define AT_NORMAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * for these functions, "f" is the random number generator function which must
 * return an unsigned integer in the range [0, 2^32), and "v" will be the
 * necessary data that is passed to that function.
 */

/**
 * returns a random number according to the normal distribution.
 */
double at_get_next_normal(
        uint32_t (*f)(void *), void *v, double mean, double dev);
/**
 * returns a random number according to the log-normal distribution.
 */
double at_get_next_lognormal(
        uint32_t (*f)(void *), void *v, double mean, double dev);
/**
 * returns a random number according to the normal distribution, where "n" is
 * the degrees of freedom.
 */
double at_get_next_chi_squared(uint32_t (*f)(void *), void *v, double n);
/**
 * returns a random number according to the cauchy distribution.
 */
double at_get_next_cauchy(
        uint32_t (*f)(void *), void *v, double median, double dev);
/**
 * returns a random number according to the fischer-f distribution.
 */
double at_get_next_fischer_f(
        uint32_t (*f)(void *), void *v, double m, double n);

#ifdef __cplusplus
}
#endif

#endif
