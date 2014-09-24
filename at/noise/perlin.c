
#include "perlin.h"



void at_perlin_seed(struct at_perlin *per, uint32_t (*f)(void *), void *v)
{
	(void)per;
	(void)f;
	(void)v;
}



double at_perlin_get_1d(struct at_perlin *per, double x)
{
	(void)per;
	(void)x;
	return 0.0;
}



double at_perlin_get_2d(struct at_perlin *per, double x, double y)
{
	(void)per;
	(void)x;
	(void)y;
	return 0.0;
}



double at_perlin_get_3d(struct at_perlin *per, double x, double y, double z)
{
	(void)per;
	(void)x;
	(void)y;
	(void)z;
	return 0.0;
}



double at_perlin_get_4d(
        struct at_perlin *per, double x, double y, double z, double w)
{
	(void)per;
	(void)x;
	(void)y;
	(void)z;
	(void)w;
	return 0.0;
}
