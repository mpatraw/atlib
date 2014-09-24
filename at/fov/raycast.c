
#include <stdlib.h>

#include "raycast.h"



#define SQ(x) ((x) * (x))



static void ray(int *view, int *grid, size_t w, size_t h, double r, int x0,
                int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;
	int x = x0;
	int y = y0;

	for (; ; ) {
		if (x >= 0 && y >= 0 && (size_t)x < w && (size_t)y < h) {
			view[y * w + x] = 1;
			if (grid[y * w + x]) {
				break;
			}
			if (SQ(x - x0) + SQ(y - y0) >= SQ(r)) {
				break;
			}
		}

		if (x == x1 && y == y1) {
			break;
		}
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x += sx;
		}
		if (e2 < dy) {
			err += dx;
			y += sy;
		}
	}
}



void at_do_raycast_fov(int *view, int *grid, size_t w, size_t h, double r,
                       int cx, int cy)
{
	int v;

	for (v = cx - r; v <= cx + r; ++v) {
		ray(view, grid, w, h, r, cx, cy, v, cy - r);
	}

	for (v = cx - r; v <= cx + r; ++v) {
		ray(view, grid, w, h, r, cx, cy, v, cy + r);
	}

	for (v = cy - r; v <= cy + r; ++v) {
		ray(view, grid, w, h, r, cx, cy, cx - r, v);
	}

	for (v = cy - r; v <= cy + r; ++v) {
		ray(view, grid, w, h, r, cx, cy, cx + r, v);
	}
}
