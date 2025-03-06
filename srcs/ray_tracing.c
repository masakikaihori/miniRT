#include "../includes/mini_rt.h"

void	set_hit(t_hit *hit, int color, float t)
{
	hit->t = t;
	hit->color = color;
	return ;
}

void	ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera)
{
	float	t;
	float	f[4];

	f[A] = pow(vec_norm(ray), 2.0);
	f[B] = 2 * (innner_product(camera, ray) - innner_product(obj.coord, ray));
	f[C] = pow(vec_norm(vec_subtraction(camera, obj.coord)), 2.0) - pow(obj.diameter, 2.0);
	f[D] = pow(f[B], 2.0) - (4 * f[A] * f[C]);
	if (f[D] == 0)
	{
		t = -f[B] / (2 * f[A]);
		if (t >= 0 && (hit->t == -1 || hit->t > t))
		set_hit(hit, obj.color, t);
	}
	if (f[D] > 0)
	{
		t = (-f[B] + f[D]) / (2 * f[A]);
		if (t >= 0 && (hit->t == -1 || hit->t > t))
			set_hit(hit, obj.color, t);
		t = (-f[B] - f[D]) / (2 * f[A]);
		if (t >= 0 && (hit->t == -1 || hit->t > t))
			set_hit(hit, obj.color, t);
	}
	return ;
}

void	ray_plane(t_xyz ray, t_plane obj, t_hit *hit, t_xyz camera)
{
	float	t;
	float	d;

	d = innner_product(vec_multiplied(-1, ray), obj.vec);
	if (d != 0)
	{
		t = innner_product(vec_subtraction(camera, obj.coord), obj.vec) / d;
		if (t >= 0 && (hit->t == -1 || hit->t > t))
			set_hit(hit, obj.color, t);
	}
	return ;
}

// void	ray_cylinder(t_xyz ray, t_object *tmp_obj, t_hit *hit)
// {
// 	float	t;

// 	if (t > 0 && hit->t > t)
// 	{
// 		hit->t = t;
// 		hit->colors = tmp_obj->info.cylinder.colors;
// 		hit->color = tmp_obj->info.cylinder.color;
// 	}
// 	return ;
// }
