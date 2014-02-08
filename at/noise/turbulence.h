
/**
 * turbulence for noise functions
 */
#ifndef AT_TURBULENCE_H
#define AT_TURBULENCE_H

#include <stdint.h>

struct at_turbulence
{
        unsigned octants;
        double lucanarity;
        double gain;
        double amplitude;
        double frequency;
};

#ifdef __cplusplus
extern "C" {
#endif

double at_turbulence_2d(
        double (*f)(void *, double, double), void *v,
        struct at_turbulence *turb, double x, double y);
double at_turbulence_3d(
        double (*f)(void *, double, double, double), void *v,
        struct at_turbulence *turb, double x, double y, double z);
double at_turbulence_4d(
        double (*f)(void *, double, double, double, double), void *v,
        struct at_turbulence *turb, double x, double y, double z, double w);

#ifdef __cplusplus
}
#endif

#endif
