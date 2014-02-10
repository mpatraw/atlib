
#include <math.h>

#include "normal.h"



extern double at_get_next_gamma(
        double alpha, double beta, uint32_t (*f)(void *), void *v);



#define _01     (1.0 / 4294967296.0)



double at_get_next_normal(
        double mean, double dev, uint32_t (*f)(void *), void *v)
{
        const double pi = 3.14159265358979323846;
        double r1 = f(v) * _01;
        double r2 = f(v) * _01;
        double rho = sqrt(-2.0 * log(1.0 - r2));

        return rho * cos(2.0 * pi * r1) * dev + mean;
        /*return rho * sin(2 * pi * r1) * dev + mean;*/
}



double at_get_next_lognormal(
        double mean, double dev, uint32_t (*f)(void *), void *v)
{
        return exp(at_get_next_normal(mean, dev, f, v));
}



double at_get_next_chi_squared(double n, uint32_t (*f)(void *), void *v)
{
        return at_get_next_gamma(n / 2.0, 1.0, f, v) * 2;
}



double at_get_next_cauchy(
        double median, double dev, uint32_t (*f)(void *), void *v)
{
        const double pi = 3.14159265358979323846;
        double val = f(v) * _01 - 0.5;
        return median + dev * tan(pi * val);
}



double at_get_next_fischer_f(
        double m, double n, uint32_t (*f)(void *), void *v)
{
        return
                (at_get_next_chi_squared(m, f, v) * n) /
                (at_get_next_chi_squared(n, f, v) * m);
}



double at_get_next_student_t(double n, uint32_t (*f)(void *), void *v)
{
        return
                at_get_next_normal(0.0, 1.0, f, v) /
                sqrt(at_get_next_chi_squared(n, f, v) / n);
}
