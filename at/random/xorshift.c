
#include "xorshift.h"



void at_xorshift_seed(struct at_xorshift *xorshift, uint32_t seed)
{
        uint32_t *s = xorshift->_state;
        s[0] = seed;
        s[1] = 1103515245 * s[0] + 12345;
        s[2] = 1103515245 * s[1] + 12345;
        s[3] = 1103515245 * s[2] + 12345;
}



uint32_t at_xorshift_next(struct at_xorshift *xorshift)
{
        uint32_t *s = xorshift->_state;
        uint32_t t = s[0] ^ (s[0] << 11);
        s[0] = s[1];
        s[1] = s[2];
        s[2] = s[3];
        s[3] = (s[3]) ^ (s[3] >> 19) ^ (t ^ (t >> 8));
        return s[3];
}
