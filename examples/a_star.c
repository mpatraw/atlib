
#include <stdio.h>
#include <string.h>

#include <at/path.h>



#define W 20
#define H 10



static int is_obstructed(void *v, int x, int y)
{
	int *grid = (int *)v;
	return grid[y * W + x] != 0;
}



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
	int err;
	int xs[12];
	int ys[12];
	size_t sz = 12, i;

	memset(display, 0, sizeof(*display) * W * H);

	for (y = 0; y < H; ++y) {
		for (x = 0; x < W; ++x) {
			display[y * W + x] = grid[y * W + x] ? '#' : '.';
		}
	}

	err = at_path_a_star(xs, ys, &sz, 0, 0, 6, 6, W, H, is_obstructed,
	                     (void *)grid);

	if (err != 0) {
		printf("at_path_a_star() failed, returning %d\n", err);
		return -1;
	}


	for (i = 0; i < sz; ++i) {
		display[ys[i] * W + xs[i]] = '*';
	}

	for (y = 0; y < H; ++y) {
		for (x = 0; x < W; ++x) {
			printf("%c", display[y * W + x]);
		}
		printf("\n");
	}

	return 0;
}
