
/*******************************************************************************
 * bjenkins
 *
 * https://groups.google.com/forum/?fromgroups#!msg/sci.crypt.random-numbers/LAuBGOErdrk/xrMBr3guA7IJ
 */
#ifndef AT_RANDOM_BJENKINS_H
#define AT_RANDOM_BJENKINS_H

#include <stdint.h>

enum {AT_BJENKINS_K = 4};

struct at_bjenkins
{
        uint32_t _state[AT_BJENKINS_K];
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * seeds the bjenkins random number generator. must be called before calling
 * at_bjenkins_get_next
 */
void at_bjenkins_seed(struct at_bjenkins *bjenkins, uint32_t seed);
/**
 * returns the next random unsigned integer in the range [0, 2^32).
 */
uint32_t at_bjenkins_get_next(struct at_bjenkins *bjenkins);

#ifdef __cplusplus
}
#endif

#endif
