
#include <stdlib.h>
#include <string.h>


#include "a_star.h"



typedef void free_func(void *);
/* Returns 0 on equality,
 *        <0 when the first arg is less than the second,
 *        >0 when the first arg is greater than the first.
 */
typedef int comp_func(void *, void *);



struct pqueue {
	void **mem;
	unsigned length, allocd;
};



static int pqueue_init(struct pqueue *pq, unsigned size)
{
	/* Size + 1, since we don't count element 0. */
	pq->mem = malloc(sizeof *pq->mem * (size + 1));
	if (!pq->mem) {
		return -1;
	}
	pq->length = 0;
	pq->allocd = size;
	return 0;
}



static void pqueue_uninit(struct pqueue *pq, free_func *freer)
{
	unsigned i;
	if (freer)
		for (i = 1; i < pq->length + 1; ++i) {
			freer(pq->mem[i]);
		}
	free(pq->mem);
}



static int pqueue_push_min(struct pqueue *pq, void *mem, comp_func *comp)
{
	int i;
	void **new_mem;

	if (pq->length + 1 >= pq->allocd) {
		new_mem = realloc(pq->mem, sizeof *pq->mem * pq->allocd * 2);
		if (!new_mem) {
			return -1;
		}
		pq->mem = new_mem;
		pq->allocd *= 2;
	}

	for (i = ++pq->length; i > 1 && comp(pq->mem[i / 2], mem) > 0; i /= 2) {
		pq->mem[i] = pq->mem[i / 2];
	}
	pq->mem[i] = mem;

	return 0;
}



static void pqueue_pop_min(struct pqueue *pq, free_func *freer, comp_func *comp)
{
	unsigned i, child;
	void *tofree = pq->mem[1];
	void *last = pq->mem[pq->length--];
	if (freer) {
		freer(tofree);
	}

	for (i = 1; i * 2 <= pq->length; i = child) {
		child = i * 2;
		if (child != pq->length && comp(pq->mem[child], pq->mem[child + 1]) > 0) {
			child++;
		}

		if (comp(last, pq->mem[child]) > 0) {
			pq->mem[i] = pq->mem[child];
		} else {
			break;
		}
	}

	pq->mem[i] = last;
}



/*static int pqueue_push_max(struct pqueue *pq, void *mem, comp_func *comp)
{
        int i;
        void **new_mem;

        if (pq->length + 1 >= pq->allocd)
        {
                new_mem = realloc(pq->mem, sizeof *pq->mem * pq->allocd * 2);
                if (!new_mem)
                        return -1;
                pq->mem = new_mem;
                pq->allocd *= 2;
        }

        for (i = ++pq->length; i > 1 && comp(pq->mem[i / 2], mem) < 0; i /= 2)
                pq->mem[i] = pq->mem[i / 2];
        pq->mem[i] = mem;

        return 0;
}



static void pqueue_pop_max(struct pqueue *pq, free_func *freer, comp_func *comp)
{
        unsigned i, child;
        void *tofree = pq->mem[1];
        void *last = pq->mem[pq->length--];
        if (freer)
                freer(tofree);

        for (i = 1; i * 2 <= pq->length; i = child) {
                child = i * 2;
                if (child != pq->length && comp(pq->mem[child], pq->mem[child + 1]) < 0)
                        child++;

                if (comp(last, pq->mem[child]) < 0)
                        pq->mem[i] = pq->mem[child];
                else
                break;
        }

        pq->mem[i] = last;
}*/



static void pqueue_peek(struct pqueue *pq, void **mem)
{
	*mem = pq->mem[1];
}



struct a_star_node {
	struct a_star_node *parent;
	int closed;
	int x, y;
	int g, h;
};



static int pqueue_has(struct pqueue *pq, void *mem)
{
	unsigned i;
	for (i = 1; i < pq->length + 1; ++i)
		if (pq->mem[i] == mem) {
			return 1;
		}
	return 0;
}



static int heuristic(int x0, int y0, int x1, int y1)
{
	int dx = abs(x0 - x1);
	int dy = abs(y0 - y1);
	int diag = dx < dy ? dx : dy;
	int straight = dx + dy;
	return diag + (straight - 2 * diag);
}



static int a_star_node_cmp(void *a, void *b)
{
	return (((struct a_star_node *)a)->g + ((struct a_star_node *)a)->h) -
	       (((struct a_star_node *)b)->g + ((struct a_star_node *)b)->h);
}




int at_path_a_star(int *xs, int *ys, size_t *sz, int x0, int y0, int x1, int y1,
                   size_t w, size_t h, int (*is_obstructed) (void *, int, int), void *map)
{
	static int dirs[8][3] = {
		{-1,  0, 10}, { 0, -1, 10}, { 0,  1, 10}, { 1,  0, 10},
		{-1, -1, 14}, {-1,  1, 14}, { 1, -1, 14}, { 1,  1, 14},
	};

	int ret, i, nx, ny;
	int in_bounds, obstructed;
	struct a_star_node *nodes = NULL;
	struct a_star_node *ntmp = NULL, *head = NULL, *reversed = NULL;
	struct a_star_node *lowest = NULL, *neighbor = NULL;
	struct pqueue open;

	nodes = malloc(sizeof *nodes * w * h);
	if (!nodes) {
		goto nomem;
	}
	memset(nodes, 0, sizeof *nodes * w * h);

	nodes[y0 * w + x0].x = x0;
	nodes[y0 * w + x0].y = y0;

	pqueue_init(&open, 256);
	pqueue_push_min(&open, &nodes[y0 * w + x0], a_star_node_cmp);

	while (open.length) {
		pqueue_peek(&open, (void **)&lowest);
		pqueue_pop_min(&open, NULL, a_star_node_cmp);
		lowest->closed = 1;

		if (lowest->x == x1 && lowest->y == y1) {
			break;
		}

		for (i = 0; i < 8; ++i) {
			nx = lowest->x + dirs[i][0];
			ny = lowest->y + dirs[i][1];
			neighbor = &nodes[ny * w + nx];
			in_bounds = nx >= 0 && nx < w && ny >= 0 && ny < h;
			if (in_bounds) {
				obstructed = is_obstructed(map, nx, ny);
			} else {
				obstructed = 1;
			}
			if (!obstructed && !neighbor->closed) {
				if (!pqueue_has(&open, neighbor)) {
					neighbor->x = nx;
					neighbor->y = ny;
					neighbor->g = lowest->g + dirs[i][2];
					neighbor->h = heuristic(nx, ny, x1, y1);
					pqueue_push_min(&open, neighbor, a_star_node_cmp);
					neighbor->parent = lowest;
				} else if (lowest->g + dirs[i][2] < neighbor->g) {
					neighbor->g = lowest->g + dirs[i][2];
					neighbor->parent = lowest;
				}
			}
		}
	}

	if (!nodes[y1 * w + x1].parent) {
		goto nopath;
	}

	for (head = &nodes[y1 * w + x1]; head; ) {
		ntmp = head;
		head = head->parent;
		ntmp->parent = reversed;
		reversed = ntmp;
	}

	for (i = 0; reversed; reversed = reversed->parent) {
		xs[i] = reversed->x;
		ys[i] = reversed->y;
		if (++i >= *sz) {
			break;
		}
	}


	ret = 0;
	*sz = i;
	goto end;

nomem:
	ret = -1;
	*sz = 0;
	goto end;

nopath:
	ret = -2;
	*sz = 0;
	goto end;

end:
	free(nodes);
	pqueue_uninit(&open, NULL);
	return ret;
}
