
/**
 * a* pathing
 */
#ifndef AT_PATH_A_STAR_H
#define AT_PATH_A_STAR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * fills the arrays "xs" and "ys" with an a* path from (x0,y0) to (x1,y1), "sz"
 * should be the size of the arrays, to prevent overflow, and then "sz" is set
 * to the actual length of the path, this could be smaller than the array sizes.
 *
 * returns 0 on success, -1 on no memory, and -2 on no path found.
 */
int at_path_a_star(int *xs, int *ys, size_t *sz, int x0, int y0, int x1, int y1,
        size_t w, size_t h, int (*is_obstructed) (void *), void **map);

#ifdef __cplusplus
}
#endif

#endif
