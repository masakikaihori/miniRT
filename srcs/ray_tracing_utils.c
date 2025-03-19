#include "../includes/mini_rt.h"

bool	in_upcircle(t_xyz ray, t_cylinder obj, t_xyz camera, double t)
{
	double	distance;
	t_xyz	from_center;
	t_xyz	vector;

	vector = vec_addition(camera, vec_mul(t, ray));
	from_center = vec_sub(vector, vec_addition(obj.coord, obj.upside));
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

	vector = vec_addition(camera, vec_mul(t, ray));
	from_center = vec_sub(vector, vec_addition(obj.coord, obj.downside));
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

void	cal_height(t_cylinder obj, t_xyz camera, t_xyz ray, double h[2])
{
	h[0] = (obj.height / -2.0 - inner_pro(vec_sub(camera, obj.coord), obj.vec))
		/ (inner_pro(ray, obj.vec));
	h[1] = (obj.height / 2.0 - inner_pro(vec_sub(camera, obj.coord), obj.vec))
		/ (inner_pro(ray, obj.vec));
	return ;
}
