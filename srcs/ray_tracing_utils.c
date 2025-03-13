#include "../includes/mini_rt.h"

bool	in_upcircle(t_xyz ray, t_cylinder obj, t_xyz camera, double t)
{
	double	distance;
	t_xyz	from_center;
	t_xyz	vector;

	vector = vec_addition(camera, vec_multiplied(t, ray));
	from_center = vec_subtraction(vector, vec_addition(obj.coord, obj.upside));
	distance = vec_norm(from_center);
	if (distance > obj.diameter / 2.0)
		return (false);
	return (true);
}

bool	in_downcircle(t_xyz ray, t_cylinder obj, t_xyz camera, double t)
{
	double	distance;
	t_xyz	from_center;
	t_xyz	vector;

	vector = vec_addition(camera, vec_multiplied(t, ray));
	from_center = vec_subtraction(vector, vec_addition(obj.coord, obj.downside));
	distance = vec_norm(from_center);
	if (distance > obj.diameter / 2.0)
		return (false);
	return (true);
}

bool	in_height(double t, double h[2])
{
	if (h[0] <= h[1])
	{
		if (h[0] < t)
		{
			if (h[1] > t)
				return (true);
		}
	}
	else
	{
		if (h[1] < t)
		{
			if (h[0] > t)
				return (true);
		}
	}
	return (false);
}

void	set_hit_cylinder(t_hit *hit, double t, t_cylinder obj, t_cyl_inter p)
{
	hit->t = t;
	hit->colors = obj.colors;
	hit->index = obj.index;
	hit->cylinder = p;
	return ;
}

void	set_hit(t_hit *hit, t_rgb colors, double t, int index)
{
	hit->t = t;
	hit->colors = colors;
	hit->index = index;
	return ;
}