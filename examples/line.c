
#include <stdio.h>
#include <stdlib.h>

#include <at/path.h>



#define MAX(a, b) ((a) > (b) ? (a) : (b))



int main(int argc, char *argv[])
{
        int *xs;
        int *ys;
        size_t i, sz;
        int x0, y0, x1, y1;

        if (argc < 5)
        {
                printf("usage: %s x0 y0 x1 y1\n", argv[0]);
                return 0;
        }

        x0 = abs(atoi(argv[1]));
        y0 = abs(atoi(argv[2]));
        x1 = abs(atoi(argv[3]));
        y1 = abs(atoi(argv[4]));

        /* compute line length needed */
        at_path_line(NULL, NULL, &sz, x0, y0, x1, y1);
        xs = malloc(sizeof(*xs) * sz);
        ys = malloc(sizeof(*ys) * sz);

        if (!xs || !ys)
        {
                free(xs);
                free(ys);
                perror("malloc");
                return 1;
        }

        at_path_line(xs, ys, &sz, x0, y0, x1, y1);

        for (i = 0; i < sz; ++i)
                printf("%d, %d\n", xs[i], ys[i]);

        return 0;
}
