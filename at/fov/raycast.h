
/**
 * raycast field of view algorithm
 */
#ifndef AT_FOV_RAYCAST_H
#define AT_FOV_RAYCAST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void at_do_raycast_fov(int *view, int *grid, size_t w, size_t h, double r,
        int cx, int cy);

#ifdef __cplusplus
}
#endif

#endif
