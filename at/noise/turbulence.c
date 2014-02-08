
#include <math.h>

#include "turbulence.h"



struct at_2dto4d
{
        double (*f)(void *, double, double);
        void *v;
};



static double at_2dto4d(void *v, double x, double y, double z, double w)
{
        struct at_2dto4d *_ = (struct at_2dto4d *)v;
        return _->f(_->v, x, y);
}



struct at_3dto4d
{
        double (*f)(void *, double, double, double);
        void *v;
};



static double at_3dto4d(void *v, double x, double y, double z, double w)
{
        struct at_3dto4d *_ = (struct at_3dto4d *)v;
        return _->f(_->v, x, y, z);
}



double at_turbulence_2d(
        double (*f)(void *, double, double), void *v,
        struct at_turbulence *turb, double x, double y)
{
        struct at_2dto4d _;
        _.f = f;
        _.v = v;
        return at_turbulence_4d(at_2dto4d, &_, turb, x, y, 0, 0);
}



double at_turbulence_3d(
        double (*f)(void *, double, double, double), void *v,
        struct at_turbulence *turb, double x, double y, double z)
{
        struct at_3dto4d _;
        _.f = f;
        _.v = v;
        return at_turbulence_4d(at_3dto4d, &_, turb, x, y, z, 0);
}



double at_turbulence_4d(
        double (*f)(void *, double, double, double, double), void *v,
        struct at_turbulence *turb, double x, double y, double z, double w)
{
        unsigned i;

        unsigned octs = turb ? turb->octants : 6;
        double lucan = turb ? turb->lacunarity : 2.0;
        double gain = turb ? turb->gain : 0.5;
        double amp = turb ? turb->amplitude : 1.0;
        double freq = turb ? turb->frequency : 1.0;

        double sum = 0.0;

        for (i = 0; i < octs; ++i)
        {
                sum += amp * abs(f(v, x * freq, y * freq, z * freq, w * freq));
                amp *= gain;
                freq *= lucan;
        }

        return sum;
}
