
#include "mt.h"



#define M       397
#define N       AT_MT_K
#define UPPER   0x80000000ul
#define LOWER   0x7ffffffful



void at_mt_seed(struct at_mt *mt, uint32_t seed)
{
	int i;
	uint32_t *s = mt->_state;

	s[0] = seed & 0xffffffff;

	for (i = 1; i < AT_MT_K; ++i) {
		s[i] = 1812433253;
		s[i] *= s[i - 1] ^ (s[i - 1] >> 30);
		s[i] += i;
	}
	mt->_idx = AT_MT_K;
}



uint32_t at_mt_get_next(struct at_mt *mt)
{
	const uint32_t mag[2] = {0, 0x9908b0df};
	uint32_t *s = mt->_state;
	uint32_t *i = &mt->_idx;

	uint32_t y;
	if (*i >= N) {
		int k;

		for (k = 0; k < N - M; ++k) {
			y = (s[k] & UPPER) | (s[k + 1] & LOWER);
			s[k] = (s[k + M]) ^ (y >> 1) ^ (mag[y & 1]);
		}

		for (; k < N - 1; ++k) {
			y = (s[k] & UPPER) | (s[k + 1] & LOWER);
			s[k] = (s[k + (M - N)]) ^ (y >> 1) ^ (mag[y & 1]);
		}
		y = (s[N - 1] & UPPER) | (s[0] & LOWER);
		s[N - 1] = s[M - 1] ^ (y >> 1) ^ mag[y & 1];

		*i = 0;
	}

	y = s[(*i)++];

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680ul;
	y ^= (y << 15) & 0xefc60000ul;
	y ^= (y >> 18);

	return y;
}
