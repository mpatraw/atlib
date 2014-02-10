
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



static const char *test(void)
{
        mu_assert("example assert", 1 == 1);
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
