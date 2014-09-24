
/*******************************************************************************
 * mt - mersenne twister 19937
 *
 * medium speed, medium memory, period = 2^19937 - 1
 */
#ifndef AT_RANDOM_MT_H
#define AT_RANDOM_MT_H

#include "pstdint.h"

enum {AT_MT_K = 624};

struct at_mt {
	uint32_t _state[AT_MT_K];
	uint32_t _idx;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * seeds the mt random number generator. must be called before calling
 * at_mt_get_next
 */
void at_mt_seed(struct at_mt *mt, uint32_t seed);
/**
 * returns the next random unsigned integer in the range [0, 2^32).
 */
uint32_t at_mt_get_next(struct at_mt *mt);

#ifdef __cplusplus
}
#endif

#endif
