
/**
 * turbulence for noise functions
 */
#ifndef AT_NOISE_TURBULENCE_H
#define AT_NOISETURBULENCE_H

#include "pstdint.h"

struct at_turbulence {
	unsigned octants;
	double lacunarity;
	double gain;
	double amplitude;
	double frequency;
};

#ifdef __cplusplus
extern "C" {
#endif

double at_turbulence_get_2d(struct at_turbulence *turb,
                            double (*f)(void *, double, double), void *v,
                            double x, double y);
double at_turbulence_get_3d(struct at_turbulence *turb,
                            double (*f)(void *, double, double, double), void *v,
                            double x, double y, double z);
double at_turbulence_get_4d(struct at_turbulence *turb,
                            double (*f)(void *, double, double, double, double), void *v,
                            double x, double y, double z, double w);

#ifdef __cplusplus
}
#endif

#endif
