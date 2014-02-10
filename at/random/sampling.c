
#include <math.h>

#include "sampling.h"



#define _01     (1.0 / 4294967296.0)



#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))


unsigned at_get_next_discrete(
        double *w, size_t sz, uint32_t (*f)(void *), void *v)
{
        unsigned i = 0;
        double sum = 0.0;
        double accum = 0.0;
        double u = f(v) * _01;

        for (i = 0; i < sz; ++i)
                sum += w[i];


        for (i = 0; i < sz; ++i)
        {
                accum += w[i] / sum;
                if (u < accum)
                        return i;
        }

        return i;
}



double at_get_next_piecewise_constant(
        double *w, double *b, size_t sz, uint32_t (*f)(void *), void *v)
{
        size_t i = at_get_next_discrete(w, sz, f, v);
        return f(v) * _01 * (b[i + 1] - b[i]) + b[i];
}



double at_get_next_piecewise_linear(
        double *w, double *b, double *t, size_t sz,
        uint32_t (*f)(void *), void *v)
{
        double width;
        double w1;
        double w2;
        size_t i;
        int is_in_rectangle;

        for (i = 0; i < sz - 1; ++i)
        {
                width = b[i + 1] - b[i];
                w1 = w[i];
                w2 = w[i + 1];
                t[(i * 2) + 0] = MIN(w1, w2) * width;
                t[(i * 2) + 1] = fabs(w1 - w2) * width / 2;
        }


        i = at_get_next_discrete(t, (sz - 1) * 2, f, v);
        is_in_rectangle = i % 2 == 0;
        i /= 2;

        if (is_in_rectangle)
                return f(v) * _01 * (b[i + 1] - b[i]) + b[i];
        else if (w[i] < w[i + 1])
                return MAX(f(v) * _01 * (b[i + 1] - b[i]) + b[i],
                        f(v) * _01 * (b[i + 1] - b[i]) + b[i]);
        else
                return MIN(f(v) * _01 * (b[i + 1] - b[i]) + b[i],
                        f(v) * _01 * (b[i + 1] - b[i]) + b[i]);
}
