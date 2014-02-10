
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "at/fov.h"
#include "at/noise.h"
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



static const char *test(void)
{
        unsigned x, y;
#define W 20
#define H 10
        int view[W * H];
        int grid[W * H] = {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        memset(view, 0, sizeof(*view) * W * H);

        at_shadowcast(view, grid, W, H, 10.0, 10, 5);

        for (y = 0; y < H; ++y)
        {
                for (x = 0; x < W; ++x)
                {
                        if (x == 10 && y == 5)
                                printf("*");
                        else if (view[y * W + x])
                                printf("%c", grid[y * W + x] ? '#' : '.');
                        else
                                printf(" ");
                }
                printf("\n");
        }

        return NULL;
}



static const char *test_all(void)
{
        mu_run_test(test);
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
