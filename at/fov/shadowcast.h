
/**
 * shadowcast field of view algorithm
 */
#ifndef AT_FOV_SHADOWCAST_H
#define AT_FOV_SHADOWCAST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void at_do_shadowcast_fov(int *view, double r, int cx, int cy, size_t w,
                          size_t h, int (*is_opaque) (void *, int, int), void *grid);

#ifdef __cplusplus
}
#endif

#endif
