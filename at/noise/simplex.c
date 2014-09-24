
#include <math.h>

#include "simplex.h"



#define _01     2.3283064365386963e-10



static const int grad3[12][3] = {
	{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
	{1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
	{0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
};



static const int grad4[32][4]= {
	{0, 1, 1, 1},  {0, 1, 1, -1},  {0, 1, -1, 1},  {0, 1, -1, -1},
	{0, -1, 1, 1}, {0, -1, 1, -1}, {0, -1, -1, 1}, {0, -1, -1, -1},
	{1, 0, 1, 1},  {1, 0, 1, -1},  {1, 0, -1, 1},  {1, 0, -1, -1},
	{-1, 0, 1, 1}, {-1, 0, 1, -1}, {-1, 0, -1, 1}, {-1, 0, -1, -1},
	{1, 1, 0, 1},  {1, 1, 0, -1},  {1, -1, 0, 1},  {1, -1, 0, -1},
	{-1, 1, 0, 1}, {-1, 1, 0, -1}, {-1, -1, 0, 1}, {-1, -1, 0, -1},
	{1, 1, 1, 0},  {1, 1, -1, 0},  {1, -1, 1, 0},  {1, -1, -1, 0},
	{-1, 1, 1, 0}, {-1, 1, -1, 0}, {-1, -1, 1, 0}, {-1, -1, -1, 0}
};



static const int perm[256] = {
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
	36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
	234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
	88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
	134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
	230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
	1, 216, 80, 73, 209, 76, 132, 187, 208,  89, 18, 169, 200, 196, 135, 130,
	116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
	124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
	47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
	154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
	108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
	242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
	239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
	50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
	141, 128, 195, 78, 66, 215, 61, 156, 180
};



static const int simplex[64][4] = {
	{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 0, 0, 0}, {0, 2, 3, 1},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 2, 3, 0},
	{0, 2, 1, 3}, {0, 0, 0, 0}, {0, 3, 1, 2}, {0, 3, 2, 1},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 3, 2, 0},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{1, 2, 0, 3}, {0, 0, 0, 0}, {1, 3, 0, 2}, {0, 0, 0, 0},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {2, 3, 0, 1}, {2, 3, 1, 0},
	{1, 0, 2, 3}, {1, 0, 3, 2}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{0, 0, 0, 0}, {2, 0, 3, 1}, {0, 0, 0, 0}, {2, 1, 3, 0},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{2, 0, 1, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{3, 0, 1, 2}, {3, 0, 2, 1}, {0, 0, 0, 0}, {3, 1, 2, 0},
	{2, 1, 0, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	{3, 1, 0, 2}, {0, 0, 0, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}
};



static double dot2(const int *g, double x, double y)
{
	return g[0] * x + g[1] * y;
}



static double dot3(const int *g, double x, double y, double z)
{
	return g[0] * x + g[1] * y + g[2] * z;
}



static double dot4(const int *g, double x, double y, double z, double w)
{
	return g[0] * x + g[1] * y + g[2] * z + g[3] * w;
}



void at_simplex_seed(struct at_simplex *sim, uint32_t (*f)(void *), void *v)
{
	unsigned i, j, t;

	for (i = 0; i < 256; ++i) {
		sim->_p[i] = perm[i];
	}

	if (f && v) {
		while (i-- > 0) {
			j = floor(f(v) * _01 * (i + 1));
			t = sim->_p[i];
			sim->_p[i] = sim->_p[j];
			sim->_p[j] = t;
		}
	}

	for (i = 0; i < 256; ++i) {
		sim->_p[i + 256] = sim->_p[i];
	}
}



double at_simplex_get_2d(struct at_simplex *sim, double x, double y)
{
	double n0, n1, n2;
	double x1, x2, y1, y2;
	int ii, jj, gi0, gi1, gi2;
	double t0, t1, t2;

	double F2 = 0.5 * (sqrt(3.0) - 1.0);

	double s = (x + y) * F2;
	int i = floor(x + s);
	int j = floor(y + s);

	double G2 = (3.0 - sqrt(3.0)) / 6.0;
	double t = (i + j) * G2;

	double X0 = i - t;
	double Y0 = j - t;

	double x0 = x - X0;
	double y0 = y - Y0;

	int i1, j1;
	if (x0 > y0) {
		i1 = 1, j1 = 0;
	} else {
		i1 = 0, j1 = 1;
	}

	x1 = x0 - i1 + G2;
	y1 = y0 - j1 + G2;
	x2 = x0 - 1.0 + 2.0 * G2;
	y2 = y0 - 1.0 + 2.0 * G2;

	ii = i & 255;
	jj = j & 255;
	gi0 = sim->_p[ii + sim->_p[jj]] % 12;
	gi1 = sim->_p[ii + i1 + sim->_p[jj + j1]] % 12;
	gi2 = sim->_p[ii + 1 + sim->_p[jj + 1]] % 12;

	t0 = 0.5 - x0 * x0 - y0 * y0;
	if (t0 < 0) {
		n0 = 0.0;
	} else {
		t0 *= t0;
		n0 = t0 * t0 * dot2(grad3[gi0], x0, y0);
	}

	t1 = 0.5 - x1 * x1 - y1 * y1;
	if (t1 < 0) {
		n1 = 0.0;
	} else {
		t1 *= t1;
		n1 = t1 * t1 * dot2(grad3[gi1], x1, y1);
	}

	t2 = 0.5 - x2 * x2 - y2 * y2;
	if (t2<0) {
		n2 = 0.0;
	} else {
		t2 *= t2;
		n2 = t2 * t2 * dot2(grad3[gi2], x2, y2);
	}

	return 70.0 * (n0 + n1 + n2);
}



double at_simplex_get_3d(struct at_simplex *sim, double x, double y, double z)
{
	double n0, n1, n2, n3;
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;
	int ii, jj, kk, gi0, gi1, gi2, gi3;
	double t0, t1, t2, t3;

	double F3 = 1.0 / 3.0;
	double s = (x + y + z) * F3;
	int i = floor(x + s);
	int j = floor(y + s);
	int k = floor(z + s);

	double G3 = 1.0 / 6.0;
	double t = (i + j + k) * G3;
	double X0 = i - t;
	double Y0 = j - t;
	double Z0 = k - t;
	double x0 = x - X0;
	double y0 = y - Y0;
	double z0 = z - Z0;

	int i1, j1, k1;
	int i2, j2, k2;

	if (x0 >= y0) {
		if (y0 >= z0) {
			i1 = 1, j1 = 0, k1 = 0, i2 = 1, j2 = 1, k2 = 0;
		} else if (x0 >= z0) {
			i1 = 1, j1 = 0, k1 = 0, i2 = 1, j2 = 0, k2 = 1;
		} else {
			i1 = 0, j1 = 0, k1 = 1, i2 = 1, j2 = 0, k2 = 1;
		}
	} else {
		if (y0 < z0) {
			i1 = 0, j1 = 0, k1 = 1, i2 = 0, j2 = 1, k2 = 1;
		} else if (x0 < z0) {
			i1 = 0, j1 = 1, k1 = 0, i2 = 0, j2 = 1, k2 = 1;
		} else {
			i1 = 0, j1 = 1, k1 = 0, i2 = 1, j2 = 1, k2 = 0;
		}
	}

	x1 = x0 - i1 + G3;
	y1 = y0 - j1 + G3;
	z1 = z0 - k1 + G3;
	x2 = x0 - i2 + 2.0 * G3;
	y2 = y0 - j2 + 2.0 * G3;
	z2 = z0 - k2 + 2.0 * G3;
	x3 = x0 - 1.0 + 3.0 * G3;
	y3 = y0 - 1.0 + 3.0 * G3;
	z3 = z0 - 1.0 + 3.0 * G3;

	ii = i & 255;
	jj = j & 255;
	kk = k & 255;
	gi0 = sim->_p[ii + sim->_p[jj + sim->_p[kk]]] % 12;
	gi1 = sim->_p[ii + i1 + sim->_p[jj + j1 + sim->_p[kk + k1]]] % 12;
	gi2 = sim->_p[ii + i2 + sim->_p[jj + j2 + sim->_p[kk + k2]]] % 12;
	gi3 = sim->_p[ii + 1 + sim->_p[jj + 1 + sim->_p[kk + 1]]] % 12;

	t0 = 0.6 - x0 * x0 - y0 * y0 - z0 * z0;
	if (t0 < 0) {
		n0 = 0.0;
	} else {
		t0 *= t0;
		n0 = t0 * t0 * dot3(grad3[gi0], x0, y0, z0);
	}

	t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1;
	if (t1 < 0) {
		n1 = 0.0;
	} else {
		t1 *= t1;
		n1 = t1 * t1 * dot3(grad3[gi1], x1, y1, z1);
	}

	t2 = 0.6 - x2 * x2 - y2 * y2 - z2 * z2;
	if (t2 < 0) {
		n2 = 0.0;
	} else {
		t2 *= t2;
		n2 = t2 * t2 * dot3(grad3[gi2], x2, y2, z2);
	}

	t3 = 0.6 - x3 * x3 - y3 * y3 - z3 * z3;
	if (t3 < 0) {
		n3 = 0.0;
	} else {
		t3 *= t3;
		n3 = t3 * t3 * dot3(grad3[gi3], x3, y3, z3);
	}

	return 32.0 * (n0 + n1 + n2 + n3);
}



double at_simplex_get_4d(
        struct at_simplex *sim, double x, double y, double z, double w)
{
	double F4 = (sqrt(5.0) - 1.0) / 4.0;
	double G4 = (5.0 - sqrt(5.0)) / 20.0;
	double n0, n1, n2, n3, n4;
	double t0, t1, t2, t3, t4;
	double x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4;
	int ii, jj, kk, ll, gi0, gi1, gi2, gi3, gi4;

	double s = (x + y + z + w) * F4;
	int i = floor(x + s);
	int j = floor(y + s);
	int k = floor(z + s);
	int l = floor(w + s);
	double t = (i + j + k + l) * G4;
	double X0 = i - t;
	double Y0 = j - t;
	double Z0 = k - t;
	double W0 = l - t;

	double x0 = x - X0;
	double y0 = y - Y0;
	double z0 = z - Z0;
	double w0 = w - W0;

	int c1 = (x0 > y0) ? 32 : 0;
	int c2 = (x0 > z0) ? 16 : 0;
	int c3 = (y0 > z0) ? 8 : 0;
	int c4 = (x0 > w0) ? 4 : 0;
	int c5 = (y0 > w0) ? 2 : 0;
	int c6 = (z0 > w0) ? 1 : 0;
	int c = c1 + c2 + c3 + c4 + c5 + c6;

	int i1, j1, k1, l1;
	int i2, j2, k2, l2;
	int i3, j3, k3, l3;

	i1 = simplex[c][0] >= 3 ? 1 : 0;
	j1 = simplex[c][1] >= 3 ? 1 : 0;
	k1 = simplex[c][2] >= 3 ? 1 : 0;
	l1 = simplex[c][3] >= 3 ? 1 : 0;

	i2 = simplex[c][0] >= 2 ? 1 : 0;
	j2 = simplex[c][1] >= 2 ? 1 : 0;
	k2 = simplex[c][2] >= 2 ? 1 : 0;
	l2 = simplex[c][3] >= 2 ? 1 : 0;

	i3 = simplex[c][0] >= 1 ? 1 : 0;
	j3 = simplex[c][1] >= 1 ? 1 : 0;
	k3 = simplex[c][2] >= 1 ? 1 : 0;
	l3 = simplex[c][3] >= 1 ? 1 : 0;

	x1 = x0 - i1 + G4;
	y1 = y0 - j1 + G4;
	z1 = z0 - k1 + G4;
	w1 = w0 - l1 + G4;
	x2 = x0 - i2 + 2.0 * G4;
	y2 = y0 - j2 + 2.0 * G4;
	z2 = z0 - k2 + 2.0 * G4;
	w2 = w0 - l2 + 2.0 * G4;
	x3 = x0 - i3 + 3.0 * G4;
	y3 = y0 - j3 + 3.0 * G4;
	z3 = z0 - k3 + 3.0 * G4;
	w3 = w0 - l3 + 3.0 * G4;
	x4 = x0 - 1.0 + 4.0 * G4;
	y4 = y0 - 1.0 + 4.0 * G4;
	z4 = z0 - 1.0 + 4.0 * G4;
	w4 = w0 - 1.0 + 4.0 * G4;


	ii = i & 255;
	jj = j & 255;
	kk = k & 255;
	ll = l & 255;
	gi0 = sim->_p[ii + sim->_p[jj + sim->_p[kk + sim->_p[ll]]]] % 32;
	gi1 = sim->_p[ii + i1 +
	              sim->_p[jj + j1 + sim->_p[kk + k1 + sim->_p[ll + l1]]]] % 32;
	gi2 = sim->_p[ii + i2 +
	              sim->_p[jj + j2 + sim->_p[kk + k2 + sim->_p[ll + l2]]]] % 32;
	gi3 = sim->_p[ii + i3 +
	              sim->_p[jj + j3 + sim->_p[kk + k3 + sim->_p[ll + l3]]]] % 32;
	gi4 = sim->_p[ii + 1 +
	              sim->_p[jj + 1 + sim->_p[kk + 1 + sim->_p[ll + 1]]]] % 32;


	t0 = 0.6 - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
	if (t0 < 0) {
		n0 = 0.0;
	} else {
		t0 *= t0;
		n0 = t0 * t0 * dot4(grad4[gi0], x0, y0, z0, w0);
	}

	t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
	if (t1 < 0) {
		n1 = 0.0;
	} else {
		t1 *= t1;
		n1 = t1 * t1 * dot4(grad4[gi1], x1, y1, z1, w1);
	}

	t2 = 0.6 - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
	if  (t2  <  0) {
		n2 = 0.0;
	} else {
		t2 *= t2;
		n2 = t2 * t2 * dot4(grad4[gi2], x2, y2, z2, w2);
	}

	t3 = 0.6 - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
	if (t3 < 0) {
		n3 = 0.0;
	} else {
		t3 *= t3;
		n3 = t3 * t3 * dot4(grad4[gi3], x3, y3, z3, w3);
	}

	t4 = 0.6 - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
	if (t4 < 0) {
		n4 = 0.0;
	} else {
		t4 *= t4;
		n4 = t4 * t4 * dot4(grad4[gi4], x4, y4, z4, w4);
	}

	return 27.0 * (n0 + n1 + n2 + n3 + n4);
}
