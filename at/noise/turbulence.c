
#include <math.h>

#include "turbulence.h"



struct at_2d {
	double (*f)(void *, double, double);
	void *v;
};



static double at_2dto4d(void *v, double x, double y, double z, double w)
{
	struct at_2d *_ = (struct at_2d *)v;
	(void)z;
	(void)w;
	return _->f(_->v, x, y);
}



struct at_3d {
	double (*f)(void *, double, double, double);
	void *v;
};



static double at_3dto4d(void *v, double x, double y, double z, double w)
{
	struct at_3d *_ = (struct at_3d *)v;
	(void)w;
	return _->f(_->v, x, y, z);
}



double at_turbulence_get_2d(struct at_turbulence *turb,
                            double (*f)(void *, double, double), void *v,
                            double x, double y)
{
	struct at_2d _;
	_.f = f;
	_.v = v;
	return at_turbulence_get_4d(turb, at_2dto4d, &_, x, y, 0, 0);
}



double at_turbulence_get_3d(struct at_turbulence *turb,
                            double (*f)(void *, double, double, double), void *v,
                            double x, double y, double z)
{
	struct at_3d _;
	_.f = f;
	_.v = v;
	return at_turbulence_get_4d(turb, at_3dto4d, &_, x, y, z, 0);
}



double at_turbulence_get_4d(struct at_turbulence *turb,
                            double (*f)(void *, double, double, double, double), void *v,
                            double x, double y, double z, double w)
{
	int i;

	int octs = turb ? turb->octants : 6;
	double lucan = turb ? turb->lacunarity : 2.0;
	double gain = turb ? turb->gain : 0.5;
	double amp = turb ? turb->amplitude : 1.0;
	double freq = turb ? turb->frequency : 1.0;

	double sum = 0.0;

	for (i = 0; i < octs; ++i) {
		sum += amp * fabs(f(v, x * freq, y * freq, z * freq, w * freq));
		amp *= gain;
		freq *= lucan;
	}

	return sum;
}
