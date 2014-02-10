
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <at/random.h>



uint32_t next(void *rng)
{
        return at_xorshift_get_next(rng);
}



int main(int argc, char *argv[])
{
        /* weights */
        double w[4] = {0, 1, 1, 0};
        /* values */
        double v[4] =  {0, 5, 10, 15};
        /* temporary storage, (sz - 1) * 2 */
        double t[6];
        int i, counter[15] = {0};
        struct at_xorshift x;
        at_xorshift_seed(&x, time(NULL));

        for (i = 0; i < 100000; ++i)
                ++counter[(int)at_get_next_piecewise_linear(w, v, t, 4, next, &x)];

        printf("100000 tests\n");
        for (i = 0; i < 15; ++i)
                printf("[%d]: %d\n", i, counter[i]);

        return 0;
}
