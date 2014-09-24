
/*******************************************************************************
 * cmwc - complimentary multiply with carry
 *
 * medium speed, high memory, period ~= 2^131104
 */
#ifndef AT_RANDOM_CMWC_H
#define AT_RANDOM_CMWC_H

#include "pstdint.h"

enum {AT_CMWC_K = 4096};

struct at_cmwc {
	uint32_t _state[AT_CMWC_K];
	uint32_t _carry;
	uint32_t _idx;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * seeds the cmwc random number generator. must be called before calling
 * at_cmwc_get_next
 */
void at_cmwc_seed(struct at_cmwc *cmwc, uint32_t seed);
/**
 * returns the next random unsigned integer in the range [0, 2^32).
 */
uint32_t at_cmwc_get_next(struct at_cmwc *cmwc);

#ifdef __cplusplus
}
#endif

#endif
