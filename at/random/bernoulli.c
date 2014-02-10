
#include <math.h>

#include "bernoulli.h"



#define _01     (1.0 / 4294967296.0)



int at_get_next_bernoulli(uint32_t (*f)(void *), void *v, double p)
{
        return f(v) * _01 < p;
}



unsigned at_get_next_binomial(
        uint32_t (*f)(void *), void *v, unsigned t, double p)
{
        unsigned i;
        unsigned count = 0;

        for (i = 0; i < t; ++i)
                if (f(v) * _01 < p)
                        count++;

        return count;
}



unsigned at_get_next_negative_binomial(
        uint32_t (*f)(void *), void *v, unsigned k, double p)
{
        unsigned kcount = 0;
        unsigned count = 0;

        while (kcount != k)
                if (f(v) * _01 < p)
                        kcount++;
                else
                        count++;

        return count;
}



unsigned at_get_next_geometric(uint32_t (*f)(void *), void *v, double p)
{
        double x = 1.0 - f(v) * _01;
        return floor(log(x) / log(1 - p));
}
