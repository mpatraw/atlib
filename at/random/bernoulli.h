
/**
 * bernoulli distribution functions
 */
#ifndef AT_RANDOM_BERNOULLI_H
#define AT_RANDOM_BERNOULLI_H

#include "pstdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * for these functions, "f" is the random number generator function which must
 * return an int integer in the range [0, 2^32), and "v" will be the
 * necessary data that is passed to that function.
 */

/**
 * returns 1 with the probability "p".
 */
int at_get_next_bernoulli(double p, uint32_t (*f)(void *), void *v);
/**
 * returns the number of test successes after trying "t" times, each test
 * succeeds with the probability "p".
 */
int at_get_next_binomial(int t, double p, uint32_t (*f)(void *), void *v);
/**
 * returns the number of test failures before reaching "k" success, each test
 * succeeds with the probability "p".
 */
int at_get_next_negative_binomial(int k, double p, uint32_t (*f)(void *),
                                  void *v);
/**
 * returns the number of test faiures before reaching a single success, each
 * test succeeds with the probability "p".
 */
int at_get_next_geometric(double p, uint32_t (*f)(void *), void *v);

#ifdef __cplusplus
}
#endif

#endif
