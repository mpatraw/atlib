
#include <math.h>

#include "fbm.h"



struct at_2d
{
        double (*f)(void *, double, double);
        void *v;
};



static double at_2dto4d(void *v, double x, double y, double z, double w)
{
        struct at_2d *_ = (struct at_2d *)v;
        return _->f(_->v, x, y);
}



struct at_3d
{
        double (*f)(void *, double, double, double);
        void *v;
};



static double at_3dto4d(void *v, double x, double y, double z, double w)
{
        struct at_3d *_ = (struct at_3d *)v;
        return _->f(_->v, x, y, z);
}



double at_fbm_2d(
        double (*f)(void *, double, double), void *v,
        struct at_fbm *fbm, double x, double y)
{
        struct at_2d _;
        _.f = f;
        _.v = v;
        return at_fbm_4d(at_2dto4d, &_, fbm, x, y, 0, 0);
}



double at_fbm_3d(
        double (*f)(void *, double, double, double), void *v,
        struct at_fbm *fbm, double x, double y, double z)
{
        struct at_3d _;
        _.f = f;
        _.v = v;
        return at_fbm_4d(at_3dto4d, &_, fbm, x, y, z, 0);
}



double at_fbm_4d(
        double (*f)(void *, double, double, double, double), void *v,
        struct at_fbm *fbm, double x, double y, double z, double w)
{
        unsigned i;

        unsigned octs = fbm ? fbm->octants : 6;
        double lucan = fbm ? fbm->lacunarity : 2.0;
        double gain = fbm ? fbm->gain : 0.5;
        double amp = fbm ? fbm->amplitude : 1.0;
        double freq = fbm ? fbm->frequency : 1.0;

        double sum = 0.0;

        for (i = 0; i < octs; ++i)
        {
                sum += amp * f(v, x * freq, y * freq, z * freq, w * freq);
                amp *= gain;
                freq *= lucan;
        }

        return sum;
}
