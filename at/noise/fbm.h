
/**
 * fractal brownian moition for noise functions
 */
#ifndef AT_NOISE_FBM_H
#define AT_NOISE_FBM_H

#include "pstdint.h"

struct at_fbm {
	unsigned octants;
	double lacunarity;
	double gain;
	double amplitude;
	double frequency;
};

#ifdef __cplusplus
extern "C" {
#endif

double at_fbm_get_2d(struct at_fbm *fbm,
                     double (*f)(void *, double, double), void *v, double x, double y);
double at_fbm_get_3d(struct at_fbm *fbm,
                     double (*f)(void *, double, double, double), void *v,
                     double x, double y, double z);
double at_fbm_get_4d(struct at_fbm *fbm,
                     double (*f)(void *, double, double, double, double), void *v,
                     double x, double y, double z, double w);

#ifdef __cplusplus
}
#endif

#endif
