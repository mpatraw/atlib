
#include <stdio.h>
#include <stdlib.h>

#include <at/path.h>



#define MAX(a, b) ((a) > (b) ? (a) : (b))



int main(int argc, char *argv[])
{
        int *path;
        unsigned i, sz;
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

        /* twice the normal size for x and y coordinates */
        path = malloc(sizeof(*path) * (MAX(abs(x1 - x0), abs(y1 - y0)) + 1) * 2);

        if (!path)
        {
                perror("malloc");
                return 1;
        }

        at_path_line(path, &sz, x0, y0, x1, y1);

        for (i = 0; i < sz; ++i)
                printf("%d, %d\n", path[(i * 2)], path[(i * 2) + 1]);

        return 0;
}
