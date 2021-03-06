
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <at/random.h>



/**
 * for the sake of keeping things as decoupled as possible, you must create a
 * function for generating random numbers to pass to the distribution functions.
 */
uint32_t next(void *rng)
{
	return at_xorshift_get_next(rng);
}



int main(int argc, char *argv[])
{
	int i, n, sum = 0;
	struct at_xorshift x;
	at_xorshift_seed(&x, time(NULL));

	if (argc < 3) {
		printf("usage: %s ndice sides\n", argv[0]);
		return 0;
	}

	/* roll XdY */
	for (i = 0; i < atoi(argv[1]); ++i) {
		n = at_get_next_uniform_i(1, abs(atoi(argv[2])), next, &x);
		printf("%d\n", n);
		sum += n;
	}
	/* and print the sum */
	printf("sum: %d\n", sum);

	return 0;
}
