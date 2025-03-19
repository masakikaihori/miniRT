#include "../includes/mini_rt.h"

void	cal_color(t_hit *hit, t_rgb t, double ratio)
{
	double	red;
	double	green;
	double	blue;

	red = (t.red * ratio / 255.0 + t.red * hit->diff / 255.0 + hit->spec) * 255.0;
	green = (t.green * ratio / 255.0 + t.green * hit->diff / 255.0 + hit->spec) * 255.0;
	blue = (t.blue * ratio / 255.0 + t.blue * hit->diff / 255.0 + hit->spec) * 255.0;
	if (red >= 255)
	red = 255;
	else if (red < 0)
	red = 0;
	if (green >= 255)
	green = 255;
	else if (green < 0)
	green = 0;
	if (blue >= 255)
	blue = 255;
	else if (blue < 0)
	blue = 0;
	hit->color
		= int_color((int)round(red), (int)round(green), (int)round(blue));
	return ;
}
