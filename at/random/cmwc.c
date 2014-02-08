
#include "cmwc.h"



void at_cmwc_seed(struct at_cmwc *cmwc, uint32_t seed)
{
        int i;
        uint32_t *s = cmwc->_state;

        s[0] = seed;
        for (i = 1; i < AT_CMWC_K; ++i)
                s[i] = (1103515245 * s[i - 1]) + 12345;

        cmwc->_carry = (1103515245 * s[AT_CMWC_K - 1]) + 12345;
        /* clamp to value recommended by george marsaglia */
        cmwc->_carry %= 809430660;
        cmwc->_idx = AT_CMWC_K - 1;
}



uint32_t at_cmwc_next(struct at_cmwc *cmwc)
{
        uint32_t *s = cmwc->_state;
        uint32_t *c = &cmwc->_carry;
        uint32_t *i = &cmwc->_idx;

        /* this is when 64-bit ints are available
        *i = (*i + 1) & (AT_CMWC_K - 1);
        uint64_t t = 18782ll * s[*i] + *c;
        *c = t >> 32;
        uint32_t x = t + *c;
        if (x < *c)
        {
                x++;
                (*c)++;
        }
        s[*i] = 0xfffffffe - x;

        return s[*i];
        */

        uint32_t th, tl, q, qh, ql, a = 18782;
        uint32_t x;

        *i = (*i + 1) & (AT_CMWC_K - 1);

        q = s[*i];
        qh = q >> 16;
        ql = q & 0xffff;

        tl = a * q + *c;
        th = (a * qh + (((*c & 0xffff) + a * ql) >> 16) + (*c >> 16)) >> 16;

        *c = th;
        x = tl + th;
        if (x < *c)
        {
                x++;
                (*c)++;
        }
        s[*i] = 0xfffffffe - x;
        return s[*i];
}
