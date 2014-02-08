
/*******************************************************************************
 * cmwc
 *
 * medium speed, high memory, period ~= 2^131104
 */
#ifndef AT_CMWC_H
#define AT_CMWC_H

#include <stdint.h>

enum {AT_CMWC_K = 4096};

struct at_cmwc
{
        uint32_t _state[AT_CMWC_K];
        uint32_t _carry;
        uint32_t _idx;
};

#ifdef __cplusplus
extern "C" {
#endif

void at_cmwc_seed(struct at_cmwc *cmwc, uint32_t seed);
uint32_t at_cmwc_next(struct at_cmwc *cmwc);

#ifdef __cplusplus
}
#endif

#endif
