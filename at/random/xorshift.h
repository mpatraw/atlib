
/*******************************************************************************
 * xorshift
 *
 * fast speed, low memory, period = 2^128 - 1
 */
#ifndef AT_RANDOM_XORSHIFT_H
#define AT_RANDOM_XORSHIFT_H

#include <stdint.h>

enum {AT_XORSHIFT_K = 4};

struct at_xorshift
{
        uint32_t _state[AT_XORSHIFT_K];
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * seeds the xorshift random number generator. must be called before calling
 * at_xorshift_get_next
 */
void at_xorshift_seed(struct at_xorshift *xorshift, uint32_t seed);
/**
 * returns the next random unsigned integer in the range [0, 2^32).
 */
uint32_t at_xorshift_get_next(struct at_xorshift *xorshift);

#ifdef __cplusplus
}
#endif

#endif
