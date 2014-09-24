
#include <math.h>

#include "bernoulli.h"



#define _01     (1.0 / 4294967296.0)



int at_get_next_bernoulli(double p, uint32_t (*f)(void *), void *v)
{
	return f(v) * _01 < p;
}



int at_get_next_binomial(int t, double p, uint32_t (*f)(void *), void *v)
{
	int i;
	int count = 0;

	for (i = 0; i < t; ++i)
		if (f(v) * _01 < p) {
			count++;
		}

	return count;
}



int at_get_next_negative_binomial(int k, double p, uint32_t (*f)(void *),
                                  void *v)
{
	int kcount = 0;
	int count = 0;

	while (kcount != k)
		if (f(v) * _01 < p) {
			kcount++;
		} else {
			count++;
		}

	return count;
}



int at_get_next_geometric(double p, uint32_t (*f)(void *), void *v)
{
	double x = 1.0 - f(v) * _01;
	return floor(log(x) / log(1 - p));
}
