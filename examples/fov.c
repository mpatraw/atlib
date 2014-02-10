
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <at/fov.h>
#include <at/noise.h>
#include <at/random.h>



#define W 20
#define H 10



int main(int argc, char *argv[])
{
        unsigned x, y;
        int view[W * H];
        int grid[W * H] = {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        memset(view, 0, sizeof(*view) * W * H);

        at_do_shadowcast_fov(view, grid, W, H, 10.0, 10, 5);

        for (y = 0; y < H; ++y)
        {
                for (x = 0; x < W; ++x)
                {
                        if (x == 10 && y == 5)
                                printf("*");
                        else if (view[y * W + x])
                                printf("%c", grid[y * W + x] ? '#' : '.');
                        else
                                printf(" ");
                }
                printf("\n");
        }

        return 0;
}
