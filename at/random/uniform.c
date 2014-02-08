
#include <math.h>

#include "uniform.h"



#define _01     2.3283064365386963e-10



int32_t at_next_uniform_i(at_next_func *f, void *v, int32_t l, int32_t u)
{
        return floor(f(v) * _01 * (u - l + 1) + l);
}



double at_next_uniform_d(at_next_func *f, void *v, double l, double u)
{
        return f(v) * _01 * (u - l) + l;
}
