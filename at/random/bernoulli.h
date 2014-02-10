
/**
 * bernoulli distribution functions
 */
#ifndef AT_BERNOULLI_H
#define AT_BERNOULLI_H

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
 * returns 1 with the probability "p".
 */
int at_get_next_bernoulli(uint32_t (*f)(void *), void *v, double p);
/**
 * returns the number of test successes after trying "t" times, each test
 * succeeds with the probability "p".
 */
unsigned at_get_next_binomial(
        uint32_t (*f)(void *), void *v, unsigned t, double p);
/**
 * returns the number of test failures before reaching "k" success, each test
 * succeeds with the probability "p".
 */
unsigned at_get_next_negative_binomial(
        uint32_t (*f)(void *), void *v, unsigned k, double p);
/**
 * returns the number of test faiures before reaching a single success, each
 * test succeeds with the probability "p".
 */
unsigned at_get_next_geometric(uint32_t (*f)(void *), void *v, double p);

#ifdef __cplusplus
}
#endif

#endif
