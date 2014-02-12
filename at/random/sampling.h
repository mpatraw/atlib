
/**
 * sampling distribution functions
 */
#ifndef AT_RANDOM_SAMPLING_H
#define AT_RANDOM_SAMPLING_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned at_get_next_discrete(
        double *w, size_t sz, uint32_t (*f)(void *), void *v);
double at_get_next_piecewise_constant(
        double *w, double *b, size_t sz, uint32_t (*f)(void *), void *v);
double at_get_next_piecewise_linear(
        double *w, double *b, double *t, size_t sz,
        uint32_t (*f)(void *), void *v);

#ifdef __cplusplus
}
#endif

#endif
