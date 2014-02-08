
/*******************************************************************************
 * xorshift
 *
 * fast speed, low memory, period = 2^128 - 1
 */
#ifndef AT_XORSHIFT_H
#define AT_XORSHIFT_H

#include <stdint.h>

enum {AT_XORSHIFT_K = 4};

struct at_xorshift
{
        uint32_t _state[AT_XORSHIFT_K];
};

#ifdef __cplusplus
extern "C" {
#endif

void at_xorshift_seed(struct at_xorshift *xorshift, uint32_t seed);
uint32_t at_xorshift_next(struct at_xorshift *xorshift);

#ifdef __cplusplus
}
#endif

#endif
