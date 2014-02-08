
#ifndef AT_BERNOULLI_H
#define AT_BERNOULLI_H

#include <stdint.h>

typedef uint32_t at_next_func(void *);

#ifdef __cplusplus
extern "C" {
#endif

int at_next_bernoulli(at_next_func *f, void *v, double p);
unsigned at_next_binomial(at_next_func *f, void *v, unsigned t, double p);
unsigned at_next_negative_binomial(
        at_next_func *f, void *v, unsigned k, double p);
unsigned at_next_geometric(at_next_func *f, void *v, double p);

#ifdef __cplusplus
}
#endif

#endif
