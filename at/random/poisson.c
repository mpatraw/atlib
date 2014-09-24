
#include <math.h>

#include "poisson.h"



#define _01     (1.0 / 4294967296.0)



unsigned at_get_next_poisson(double mean, uint32_t (*f)(void *), void *v)
{
	unsigned x = 0;
	double p = exp(-mean);
	double u = f(v) * _01;

	while (u > p) {
		u -= p;
		++x;
		p = mean * p / x;
	}

	return x;
}



double at_get_next_exponential(double lambda, uint32_t (*f)(void *), void *v)
{
	return -1.0 / lambda * log(1.0 - f(v) * _01);
}



double at_get_next_gamma(
        double alpha, double beta, uint32_t (*f)(void *), void *v)
{
	const double pi = 3.14159265358979323846;
	double x;

	if (alpha == 1.0) {
		return at_get_next_exponential(1.0, f, v) * beta;
	} else if (alpha > 1.0) {
		for (; ; ) {
			double y = tan(pi * f(v) * _01);

			x = sqrt(2.0 * alpha - 1.0) * y + alpha - 1.0;

			if (x > 0.0) {
				break;
			}

			if (f(v) * _01 <=
			                (1.0 + y * y) * exp(alpha - 1.0) *
			                log(x / (alpha - 1.0)) -
			                sqrt(2.0 * alpha - 1.0 * y)) {
				break;
			}
		}
	} else {
		for (; ; ) {
			double u = f(v) * _01;
			double y = at_get_next_exponential(1.0, f, v);
			double p = exp(1.0) / (alpha + exp(1.0));
			double q;

			if (u < p) {
				x = exp(-y / alpha);
				q = p * exp(-x);
			} else {
				x = 1.0 + y;
				q = p + (1.0 - p) * pow(x, alpha - 1.0);
			}

			if (u < q) {
				break;
			}
		}
	}

	return x * beta;
}



double at_get_next_weibull(double a, double b, uint32_t (*f)(void *), void *v)
{
	return b * pow(-log(1.0 - f(v) * _01), 1.0 / a);
}



double at_get_next_extreme_value(
        double a, double b, uint32_t (*f)(void *), void *v)
{
	return a - log(-log(f(v) * _01)) * b;
}
