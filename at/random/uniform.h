
/**
 * uniform distribution functions
 */
#ifndef AT_UNIFORM_H
#define AT_UNIFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t at_uniform_i(uint32_t (*f)(void *), void *v, int32_t l, int32_t u);
double at_uniform_f(uint32_t (*f)(void *), void *v, double l, double u);

#ifdef __cplusplus
}
#endif

#endif
