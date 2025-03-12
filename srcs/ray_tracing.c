#include "../includes/mini_rt.h"

void	ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	f[4];

	f[A] = pow(vec_norm(ray), 2.0);
	f[B] = 2.0 * (innner_product(camera, ray) - innner_product(obj.coord, ray));
	f[C] = pow(vec_norm(vec_subtraction(camera, obj.coord)), 2.0)
		- pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	if (f[D] >= 0.0)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t, obj.index);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.color, t, obj.index);
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
			set_hit(hit, obj.color, t, obj.index);
	}
	return ;
}

void	ray_cylinder_side(t_xyz ray, t_cylinder obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	f[4];
	double	h[2];
	t_xyz	ray_dot_objvec;
	t_xyz	cam_center_dot_objvec;

	ray_dot_objvec = vec_subtraction(ray, vec_multiplied(innner_product(ray, obj.vec), obj.vec));
	cam_center_dot_objvec = vec_subtraction(vec_subtraction(camera, obj.coord), vec_multiplied(innner_product(vec_subtraction(camera, obj.coord), obj.vec), obj.vec));
	f[A] = pow(vec_norm(ray_dot_objvec), 2.0);
	f[B] = 2 * innner_product(cam_center_dot_objvec, ray_dot_objvec);
	f[C] = pow(vec_norm(cam_center_dot_objvec), 2.0) - pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	h[0] = (obj.height / -2.0 - innner_product(vec_subtraction(camera, obj.coord), obj.vec)) / (innner_product(ray, obj.vec));
	h[1] = (obj.height / 2.0 - innner_product(vec_subtraction(camera, obj.coord), obj.vec)) / (innner_product(ray, obj.vec));
	if (f[D] >= 0.0)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && in_height(t, h) && (hit->t == -1.0 || hit->t > t))
			set_hit_cylinder(hit, t, obj, CYL_SIDE);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t >= 0.0 && in_height(t, h) && (hit->t == -1.0 || hit->t > t))
			set_hit_cylinder(hit, t, obj, CYL_SIDE);
	}
	return ;
}

void	ray_cylinder_surface(t_xyz ray, t_cylinder obj, t_hit *hit, t_xyz camera)
{
	double	t;

	if (innner_product(ray, obj.vec) == 0)
		return ;
	t = -innner_product(vec_subtraction(camera, vec_addition(obj.coord, obj.upside)), obj.vec) / innner_product(ray, obj.vec);
	if (t >= 0.0 && in_upcircle(ray, obj, camera, t) && (hit->t == -1.0 || hit->t > t))
		set_hit_cylinder(hit, t, obj, CYL_UP);
	t = -innner_product(vec_subtraction(camera, vec_addition(obj.coord, obj.downside)), obj.vec) / innner_product(ray, obj.vec);
	if (t >= 0.0 && in_downcircle(ray, obj, camera, t) && (hit->t == -1.0 || hit->t > t))
		set_hit_cylinder(hit, t, obj, CYL_DOWN);
	return ;
}
