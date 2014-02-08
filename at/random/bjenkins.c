
#include "bjenkins.h"



#define ROT(x, k) ((x << k) | (x >> (32 - k)))



void at_bjenkins_seed(struct at_bjenkins *bjenkins, uint32_t seed)
{
        int i;
        uint32_t *s = bjenkins->_state;

        s[0] = 0xf1ea5eed;
        s[1] = s[2] = s[3] = seed;
        for (i = 0; i < 20; ++i)
                (void)at_bjenkins_next(bjenkins);
}



uint32_t at_bjenkins_next(struct at_bjenkins *bjenkins)
{
        uint32_t *s = bjenkins->_state;

        uint32_t t = s[0] - ROT(s[1], 27);
        s[0] = s[1] ^ ROT(s[2], 17);
        s[1] = s[2] + s[3];
        s[2] = s[3] + t;
        s[3] = t + s[0];

        return s[3];
}
