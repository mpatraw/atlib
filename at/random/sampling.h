
/**
 * sampling distribution functions
 */
#ifndef AT_SAMPLING_H
#define AT_SAMPLING_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned at_get_next_discrete(
        uint32_t (*f)(void *), void *v, double *w, unsigned l);
double at_get_next_piecewise_constant(
        uint32_t (*f)(void *), void *v, double *w, double *b, double l);
double at_get_next_piecewise_linear(
        uint32_t (*f)(void *), void *v,
        double *w, double *b, double *t, double l);

#ifdef __cplusplus
}
#endif

#endif
