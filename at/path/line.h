
/**
 * line pathing
 */
#ifndef AT_LINE_H
#define AT_LINE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * fills the arrays "xs" and "ys" with a line path from (x0,y0) to (x1,y1), "xs"
 * should be the size of the arrays, to prevent overflow, and then "sz" is
 * filled with the actual length of the line, this could be smaller than the
 * array sizes. "xs" and "ys" can be null, in which case "sz" will be set to the
 * minimum length of the arrays required.
 */
void at_path_line(int *xs, int *ys, size_t *sz, int x0, int y0, int x1, int y1);

#ifdef __cplusplus
}
#endif

#endif
