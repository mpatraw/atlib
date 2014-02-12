
#include <stdio.h>
#include <string.h>

#include <at/path.h>



#define W 20
#define H 10



int main(int argc, char *argv[])
{
        unsigned x, y;
        char display[W * H];
        int grid[W * H] = {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
        int xs[100];
        int ys[100];
        size_t sz = 100, i;

        memset(display, 0, sizeof(*display) * W * H);

        for (y = 0; y < H; ++y)
                for (x = 0; x < W; ++x)
                        display[y * W + x] = grid[y * W + x] ? '#' : '.';

        at_path_a_star(xs, ys, &sz, grid, W, H, 0, 0, 6, 6);


        for (i = 0; i < sz; ++i)
                display[ys[i] * W + xs[i]] = '*';

        for (y = 0; y < H; ++y)
        {
                for (x = 0; x < W; ++x)
                {
                        printf("%c", display[y * W + x]);
                }
                printf("\n");
        }

        return 0;
}
