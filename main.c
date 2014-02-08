
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "at/random.h"

#define mu_assert(message, test)                                        \
do {                                                                    \
        if (!(test)) return message;                                    \
} while (0)                                                             \

#define mu_run_test(test)                                               \
do {                                                                    \
        const char *message = test();                                   \
        tests_run++;                                                    \
        if (message) return message;                                    \
} while (0)                                                             \

int tests_run = 0;

static uint32_t next(void *r)
{
        return at_xorshift_next(r);
}

static const char *test_rng(void)
{
        double w[] = {0.0, 1.0, 1.0, 0.0};
        double b[] = {0.0, 5.0, 5.0, 10.0};
        double t[6];
        int i;
        unsigned j;
        struct at_xorshift x;
        at_xorshift_seed(&x, time(NULL));

        /*mu_assert("error, next_integer(1, 1) != 1",
                at_next_integer(r, 1, 1) == 1);*/

        for (i = 0; i < 10; ++i)
        {
                j = at_next_piecewise_linear(next, &x, w, b, t, 4);
                printf("%u\n", j);
        }

        return NULL;
}

static const char *test_all(void)
{
        mu_run_test(test_rng);
        return NULL;
}

int main(int argc, char *argv[])
{
        const char *result = test_all();
        if (result)
                printf("%s\n", result);
        else
                printf("all tests passed\n");

        return result != NULL;
}
