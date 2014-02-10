
#include "shadowcast.h"



#define SQ(x) ((x) * (x))
#define IN_BOUNDS(fov, x, y) \
        ((x) >= 0 && (y) >= 0 && (x) < (fov)->width && (y) < (fov)->height)
#define IS_OPAQUE(fov, x, y) \
        ((fov)->grid[(y) * (fov)->width + (x)])
#define CHECK_DIST(dx, dy, r) \
        (SQ(dx) + SQ(dy) <= SQ(r))



struct shadowfov
{
        int *view;
        int *grid;
        unsigned width;
        unsigned height;
        double radius;
        int x0;
        int y0;
};



void cast_light(struct shadowfov *fov,
        int row, double start, double end, int xx, int xy, int yx, int yy)
{
        double newstart = 0.0;
        int curx, cury, dx, dy, dist;
        double left, right;
        int blocked = 0, in_bounds, is_opaque, in_radius;

        if (start < end)
                return;

        for (dist = row; dist <= fov->radius && !blocked; ++dist)
        {
                dy = -dist;
                for (dx = -dist; dx <= 0; ++dx)
                {
                        curx = fov->x0 + dx * xx + dy * xy;
                        cury = fov->y0 + dx * yx + dy * yy;
                        left = (dx - 0.5) / (dy + 0.5);
                        right = (dx + 0.5) / (dy - 0.5);

                        in_bounds = IN_BOUNDS(fov, curx, cury);
                        in_radius = CHECK_DIST(dx, dy, fov->radius);
                        is_opaque = IS_OPAQUE(fov, curx, cury);

                        if (!in_bounds || start < right)
                                continue;
                        else if (end > left)
                                break;

                        if (in_radius)
                                fov->view[cury * fov->width + curx] = 1;

                        if (blocked)
                        {
                                if (is_opaque)
                                {
                                        newstart = right;
                                        continue;
                                }
                                else
                                {
                                        blocked = 0;
                                        start = newstart;
                                }
                        }
                        else
                        {
                                if (is_opaque && in_radius)
                                {
                                        blocked = 1;
                                        cast_light(fov, dist + 1, start, left,
                                                xx, xy, yx, yy);
                                        newstart = right;
                                }
                        }
                }
        }
}



void at_do_shadowcast_fov(int *view, int *grid, unsigned w, unsigned h,
        double r, int cx, int cy)
{
        static const int d[4][2] = {
                {-1, -1},
                {-1,  1},
                { 1, -1},
                { 1,  1}
        };

        struct shadowfov fov;
        unsigned i;

        fov.view = view;
        fov.grid = grid;
        fov.width = w;
        fov.height = h;
        fov.radius = r;
        fov.x0 = cx;
        fov.y0 = cy;

        for (i = 0; i < 4; ++i)
        {
                cast_light(&fov, 1, 1.0, 0.0, 0, d[i][0], d[i][1], 0);
                cast_light(&fov, 1, 1.0, 0.0, d[i][0], 0, 0, d[i][1]);
        }
}
