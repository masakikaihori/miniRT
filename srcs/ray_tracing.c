#include "../includes/mini_rt.h"

void	set_hit(t_hit *hit, int color, double t)
{
	hit->t = t;
	hit->color = color;
	return ;
}

void	ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	f[4];

	f[A] = pow(vec_norm(ray), 2.0);
	f[B] = 2.0 * (innner_product(camera, ray) - innner_product(obj.coord, ray));
	f[C] = pow(vec_norm(vec_subtraction(camera, obj.coord)), 2.0) - pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	if (f[D] >= 0.0)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t);
	}
	return ;
}

void	ray_plane(t_xyz ray, t_plane obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	d;

	d = innner_product(vec_multiplied(-1.0, ray), obj.vec);
	if (d != 0.0)
	{
		t = innner_product(vec_subtraction(camera, obj.coord), obj.vec) / d;
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t);
	}
	return ;
}

void	ray_cylinder_side(t_xyz ray, t_cylinder obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	f[4];
	t_xyz	ray_dot_objvec;
	t_xyz	cam_center_dot_objvec;

	ray_dot_objvec = vec_subtraction(ray, vec_multiplied(innner_product(ray, obj.vec), obj.vec));
	cam_center_dot_objvec = vec_subtraction(vec_subtraction(camera, obj.coord), vec_multiplied(innner_product(vec_subtraction(camera, obj.coord), obj.vec), obj.vec));
	f[A] = pow(vec_norm(ray_dot_objvec), 2.0);
	f[B] = 2 * innner_product(cam_center_dot_objvec, ray_dot_objvec);
	f[C] = pow(vec_norm(cam_center_dot_objvec), 2.0) - pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	if (f[D] >= 0.0)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t);
	}
	return ;
}

void	ray_cylinder_surface(t_xyz ray, t_cylinder obj, t_hit *hit, t_xyz camera)
{

	return ;
}
