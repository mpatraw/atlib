
/**
 * fractal brownian moition for noise functions
 */
#ifndef AT_FBM_H
#define AT_FBM_H

#include <stdint.h>

struct at_fbm
{
        unsigned octants;
        double lacunarity;
        double gain;
        double amplitude;
        double frequency;
};

#ifdef __cplusplus
extern "C" {
#endif

double at_fbm_2d(
        double (*f)(void *, double, double), void *v,
        struct at_fbm *fbm, double x, double y);
double at_fbm_3d(
        double (*f)(void *, double, double, double), void *v,
        struct at_fbm *fbm, double x, double y, double z);
double at_fbm_4d(
        double (*f)(void *, double, double, double, double), void *v,
        struct at_fbm *fbm, double x, double y, double z, double w);

#ifdef __cplusplus
}
#endif

#endif
