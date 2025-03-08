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
	if (h[0] < t)
	{
		if (h[1] > t)
			return (true);
	}
	return (false);
}

void	set_hit(t_hit *hit, int color, double t)
{
	hit->t = t;
	hit->color = color;
	return ;
}