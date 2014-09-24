
#include "shadowcast.h"



#define SQ(x) ((x) * (x))
#define IN_BOUNDS(fov, x, y) \
        ((x) >= 0 && (y) >= 0 && (x) < (fov)->width && (y) < (fov)->height)
#define IS_OPAQUE(fov, x, y) \
        ((fov)->grid[(y) * (fov)->width + (x)])
#define CHECK_DIST(dx, dy, r) \
        (SQ(dx) + SQ(dy) <= SQ(r))



struct shadowfov {
	int *view;
	double radius;
	int x0;
	int y0;
	size_t width;
	size_t height;
	int (*is_opaque) (void *, int, int);
	void *grid;
};



void cast_light(struct shadowfov *fov,
                int row, double start, double end, int xx, int xy, int yx, int yy)
{
	double newstart = 0.0;
	int curx, cury, dx, dy, dist;
	double left, right;
	int blocked = 0, in_bounds, opaque, in_radius;

	if (start < end) {
		return;
	}

	for (dist = row; dist <= fov->radius && !blocked; ++dist) {
		dy = -dist;
		for (dx = -dist; dx <= 0; ++dx) {
			curx = fov->x0 + dx * xx + dy * xy;
			cury = fov->y0 + dx * yx + dy * yy;
			left = (dx - 0.5) / (dy + 0.5);
			right = (dx + 0.5) / (dy - 0.5);

			in_bounds = IN_BOUNDS(fov, curx, cury);
			in_radius = CHECK_DIST(dx, dy, fov->radius);
			opaque = fov->is_opaque(fov->grid, curx, cury);

			if (!in_bounds || start < right) {
				continue;
			} else if (end > left) {
				break;
			}

			if (in_radius) {
				fov->view[cury * fov->width + curx] = 1;
			}

			if (blocked) {
				if (opaque) {
					newstart = right;
					continue;
				} else {
					blocked = 0;
					start = newstart;
				}
			} else {
				if (opaque && in_radius) {
					blocked = 1;
					cast_light(fov, dist + 1, start, left,
					           xx, xy, yx, yy);
					newstart = right;
				}
			}
		}
	}
}



void at_do_shadowcast_fov(int *view, double r, int cx, int cy,
                          size_t w, size_t h, int (*is_opaque) (void *, int, int), void *grid)
{
	static const int d[4][2] = {
		{-1, -1},
		{-1,  1},
		{ 1, -1},
		{ 1,  1}
	};

	struct shadowfov fov;
	size_t i;

	fov.view = view;
	fov.radius = r;
	fov.x0 = cx;
	fov.y0 = cy;
	fov.width = w;
	fov.height = h;
	fov.is_opaque = is_opaque;
	fov.grid = grid;

	for (i = 0; i < 4; ++i) {
		cast_light(&fov, 1, 1.0, 0.0, 0, d[i][0], d[i][1], 0);
		cast_light(&fov, 1, 1.0, 0.0, d[i][0], 0, 0, d[i][1]);
	}
}
