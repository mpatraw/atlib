
#include <math.h>

#include "normal.h"



double at_next_gamma(at_next_func *f, void *v, double alpha, double beta);



#define _01     (1.0 / 4294967296.0)



double at_next_normal(at_next_func *f, void *v, double mean, double dev)
{
        const double pi = 3.14159265358979323846;
        double r1 = f(v) * _01;
        double r2 = f(v) * _01;
        double rho = sqrt(-2.0 * log(1.0 - r2));

        return rho * cos(2.0 * pi * r1) * dev + mean;
        /*return rho * sin(2 * pi * r1) * dev + mean;*/
}



double at_next_lognormal(at_next_func *f, void *v, double mean, double dev)
{
        return exp(at_next_normal(f, v, mean, dev));
}



double at_next_chi_squared(at_next_func *f, void *v, double n)
{
        return at_next_gamma(f, v, n / 2.0, 1.0) * 2;
}



double at_next_cauchy(at_next_func *f, void *v, double median, double dev)
{
        const double pi = 3.14159265358979323846;
        double val = f(v) * _01 - 0.5;
        return median + dev * tan(pi * val);
}



double at_next_fischer_f(at_next_func *f, void *v, double m, double n)
{
        return
                (at_next_chi_squared(f, v, m) * n) /
                (at_next_chi_squared(f, v, n) * m);
}



double at_next_student_t(at_next_func *f, void *v, double n)
{
        return
                at_next_normal(f, v, 0.0, 1.0) /
                sqrt(at_next_chi_squared(f, v, n) / n);
}
