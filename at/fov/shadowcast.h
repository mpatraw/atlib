
#ifndef AT_SHADOWCAST_H
#define AT_SHADOWCAST_H

#ifdef __cplusplus
extern "C" {
#endif

void at_do_shadowcast_fov(int *view, int *grid, unsigned w, unsigned h,
        double r, int cx, int cy);

#ifdef __cplusplus
}
#endif

#endif