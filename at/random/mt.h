
/*******************************************************************************
 * mt19937
 *
 * medium speed, medium memory, period = 2^19937 - 1
 */
#ifndef AT_MT_H
#define AT_MT_H

#include <stdint.h>

enum {AT_MT_K = 624};

struct at_mt
{
        uint32_t _state[AT_MT_K];
        uint32_t _idx;
};

#ifdef __cplusplus
extern "C" {
#endif

void at_mt_seed(struct at_mt *mt, uint32_t seed);
uint32_t at_mt_next(struct at_mt *mt);

#ifdef __cplusplus
}
#endif

#endif
