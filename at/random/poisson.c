
#include <math.h>

#include "poisson.h"



#define _01     (1.0 / 4294967296.0)



unsigned at_next_poisson(uint32_t (*f)(void *), void *v, double mean)
{
        unsigned x = 0;
        double p = exp(-mean);
        double u = f(v) * _01;

        while (u > p)
        {
                u -= p;
                ++x;
                p = mean * p / x;
        }

        return x;
}



double at_next_exponential(uint32_t (*f)(void *), void *v, double lambda)
{
        return -1.0 / lambda * log(1.0 - f(v) * _01);
}



double at_next_gamma(uint32_t (*f)(void *), void *v, double alpha, double beta)
{
        const double pi = 3.14159265358979323846;
        double x;

        if (alpha == 1.0)
        {
                return at_next_exponential(f, v, 1.0) * beta;
        }
        else if (alpha > 1.0)
        {
                for (; ; )
                {
                        double y = tan(pi * f(v) * _01);

                        x = sqrt(2.0 * alpha - 1.0) * y + alpha - 1.0;

                        if (x > 0.0)
                                break;

                        if (f(v) * _01 <=
                                (1.0 + y * y) * exp(alpha - 1.0) *
                                log(x / (alpha - 1.0)) -
                                sqrt(2.0 * alpha - 1.0 * y))
                                break;
                }
        }
        else
        {
                for (; ; )
                {
                        double u = f(v) * _01;
                        double y = at_next_exponential(f, v, 1.0);
                        double p = exp(1.0) / (alpha + exp(1.0));
                        double q;

                        if (u < p)
                        {
                                x = exp(-y / alpha);
                                q = p * exp(-x);
                        }
                        else
                        {
                                x = 1.0 + y;
                                q = p + (1.0 - p) * pow(x, alpha - 1.0);
                        }

                        if (u < q)
                                break;
                }
        }

        return x * beta;
}



double at_next_weibull(uint32_t (*f)(void *), void *v, double a, double b)
{
        return b * pow(-log(1.0 - f(v) * _01), 1.0 / a);
}



double at_next_extreme_value(uint32_t (*f)(void *), void *v, double a, double b)
{
        return a - log(-log(f(v) * _01)) * b;
}
