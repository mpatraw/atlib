
/**
 * uniform distribution functions
 */
#ifndef AT_RANDOM_UNIFORM_H
#define AT_RANDOM_UNIFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * returns the next integer in the range [l, u]
 */
int32_t at_get_next_uniform_i(
        int32_t l, int32_t u, uint32_t (*f)(void *), void *v);
/**
 * returns the next float in the range [l, u)
 */
double at_get_next_uniform_f(
        double l, double u, uint32_t (*f)(void *), void *v);

#ifdef __cplusplus
}
#endif

#endif
