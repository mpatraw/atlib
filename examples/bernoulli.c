
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
        double chance;
        int i, n, counter[2] = {0};
        struct at_xorshift x;
        at_xorshift_seed(&x, time(NULL));

        if (argc < 3)
        {
                printf("usage: %s chance ntimes\n", argv[0]);
                return 0;
        }

        chance = atof(argv[1]);
        n = abs(atoi(argv[2]));

        for (i = 0; i < n; ++i)
                ++counter[at_get_next_bernoulli(next, &x, chance)];

        printf("%d tests with %.2f%% chance\n", n, chance * 100);
        printf("false: %d\n", counter[0]);
        printf("true : %d\n", counter[1]);

        return 0;
}
