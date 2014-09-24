
/**
 * normal distribution functions, requires poisson distribution
 */
#ifndef AT_RANDOM_NORMAL_H
#define AT_RANDOM_NORMAL_H

#include "pstdint.h"

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
        double mean, double dev, uint32_t (*f)(void *), void *v);
/**
 * returns a random number according to the log-normal distribution.
 */
double at_get_next_lognormal(
        double mean, double dev, uint32_t (*f)(void *), void *v);
/**
 * returns a random number according to the normal distribution, where "n" is
 * the degrees of freedom.
 */
double at_get_next_chi_squared(double n, uint32_t (*f)(void *), void *v);
/**
 * returns a random number according to the cauchy distribution.
 */
double at_get_next_cauchy(
        double median, double dev, uint32_t (*f)(void *), void *v);
/**
 * returns a random number according to the fischer-f distribution.
 */
double at_get_next_fischer_f(
        double m, double n, uint32_t (*f)(void *), void *v);
/**
 * returns a random number according to the student-t distribution.
 */
double at_get_next_student_t(double n, uint32_t (*f)(void *), void *v);

#ifdef __cplusplus
}
#endif

#endif
