
/**
 * bernoulli distribution functions
 */
#ifndef AT_BERNOULLI_H
#define AT_BERNOULLI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int at_next_bernoulli(uint32_t (*f)(void *), void *v, double p);
unsigned at_next_binomial(uint32_t (*f)(void *), void *v, unsigned t, double p);
unsigned at_next_negative_binomial(
        uint32_t (*f)(void *), void *v, unsigned k, double p);
unsigned at_next_geometric(uint32_t (*f)(void *), void *v, double p);

#ifdef __cplusplus
}
#endif

#endif
