
/**
 * line pathing
 */
#ifndef AT_LINE_H
#define AT_LINE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void at_path_line(int *path, size_t *sz, int x0, int y0, int x1, int y1);

#ifdef __cplusplus
}
#endif

#endif
