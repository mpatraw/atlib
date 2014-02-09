
#include <stdlib.h>

#include "raycast.h"


#define SQ(x) ((x) * (x))


static void ray(int *view, int *grid, unsigned w, unsigned h, int r,
        int x0, int y0, int x1, int y1)
{
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;
        int x = x0;
        int y = y0;

        for (; ; )
        {
                if (x >= 0 && y >= 0 && x < w && y < h)
                {
                        if (!grid[y * w + x])
                                break;
                        if (SQ(x1 - x) + SQ(y1 - y) >= SQ(r))
                                break;
                        view[y * w + x] = 1;
                }

                if (x == x1 && y == y1)
                        break;
                e2 = err;
                if (e2 >-dx) { err -= dy; x += sx; }
                if (e2 < dy) { err += dx; y += sy; }
        }
}



void at_raycast(int *view, int *grid, unsigned w, unsigned h,
        int cx, int cy, int r)
{
        unsigned v;

        for (v = cx - r; v <= cx + r; ++v)
                ray(view, grid, w, h, r, cx, cy, v, cy - r);

        for (v = cx - r; v <= cx + r; ++v)
                ray(view, grid, w, h, r, cx, cy, v, cy + r);

        for (v = cy - r; v <= cy + r; ++v)
                ray(view, grid, w, h, r, cx, cy, cx - r, v);

        for (v = cy - r; v <= cy + r; ++v)
                ray(view, grid, w, h, r, cx, cy, cx + r, v);
}