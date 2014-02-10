
#include <math.h>

#include "uniform.h"



#define _01     2.3283064365386963e-10



int32_t at_get_next_uniform_i(
        int32_t l, int32_t u, uint32_t (*f)(void *), void *v)
{
        return floor(f(v) * _01 * (u - l + 1) + l);
}



double at_get_next_uniform_f(
        double l, double u, uint32_t (*f)(void *), void *v)
{
        return f(v) * _01 * (u - l) + l;
}
