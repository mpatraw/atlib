
#include <stdlib.h>

#include "line.h"



void at_path_line(int *path, unsigned *sz, int x0, int y0, int x1, int y1)
{
        int dx = abs(x1 - x0);
        int sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0);
        int sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;
        int i = 0;

        for (;;)
        {
                /* todo: should this check be here? */
                /*if (i >= *sz - 1) break;*/
                path[i * 2 + 0] = x0;
                path[i * 2 + 1] = y0;
                i++;

                if (x0 == x1 && y0 == y1) break;
                e2 = err;
                if (e2 > -dx) { err -= dy; x0 += sx; }
                if (e2 <  dy) { err += dx; y0 += sy; }
        }

        *sz = i;
}
