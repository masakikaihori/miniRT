#include "../includes/mini_rt.h"

void	set_hit(t_hit *hit, t_rgb colors, double t, int index)
{
	hit->t = t;
	hit->colors = colors;
	hit->index = index;
	return ;
}

void	ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	f[4];

	f[A] = pow(vec_norm(ray), 2.0);
	f[B] = 2.0 * (inner_pro(camera, ray) - inner_pro(obj.coord, ray));
	f[C] = pow(vec_norm(vec_sub(camera, obj.coord)), 2.0)
		- pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	if (f[D] >= NEAR_ZERO)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t >= NEAR_ZERO && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.colors, t, obj.index);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t >= NEAR_ZERO && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.colors, t, obj.index);
	}
	return ;
}

void	ray_plane(t_xyz ray, t_plane obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	d;

	d = inner_pro(vec_mul(-1.0, ray), obj.vec);
	if (fabs(d) > NEAR_ZERO)
	{
		t = inner_pro(vec_sub(camera, obj.coord), obj.vec) / d;
		if (t >= NEAR_ZERO && (hit->t == -1.0 || hit->t > t))
			set_hit(hit, obj.colors, t, obj.index);
	}
	return ;
}

void	ray_cyl_side(t_xyz ray, t_cylinder obj, t_hit *hit, t_xyz camera)
{
	double	t;
	double	f[4];
	double	h[2];
	t_xyz	ray_dot_objvec;
	t_xyz	cam_center_dot_objvec;

	ray_dot_objvec = vec_sub(ray, vec_mul(inner_pro(ray, obj.vec), obj.vec));
	cam_center_dot_objvec = vec_sub(vec_sub(camera, obj.coord),
		vec_mul(inner_pro(vec_sub(camera, obj.coord), obj.vec), obj.vec));
	f[A] = pow(vec_norm(ray_dot_objvec), 2.0);
	f[B] = 2 * inner_pro(cam_center_dot_objvec, ray_dot_objvec);
	f[C] = pow(vec_norm(cam_center_dot_objvec), 2.0)
		- pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	cal_height(obj, camera, ray, h);
	if (f[D] >= NEAR_ZERO)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t >= NEAR_ZERO && in_height(t, h) && (hit->t == -1.0 || hit->t > t))
			set_hit_cylinder(hit, t, obj, CYL_SIDE);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t >= NEAR_ZERO && in_height(t, h) && (hit->t == -1.0 || hit->t > t))
			set_hit_cylinder(hit, t, obj, CYL_SIDE);
	}
	return ;
}

void	ray_cyl_surface(
		t_xyz ray, t_cylinder obj, t_hit *hit, t_xyz camera)
{
	double	t;

	if (inner_pro(ray, obj.vec) == 0)
		return ;
	t = -inner_pro(vec_sub(camera, vec_addition(obj.coord, obj.upside)),
			obj.vec) / inner_pro(ray, obj.vec);
	if (fabs(t) > NEAR_ZERO
		&& in_upcircle(ray, obj, camera, t) && (hit->t == -1.0 || hit->t > t))
		set_hit_cylinder(hit, t, obj, CYL_UP);
	t = -inner_pro(vec_sub(camera, vec_addition(obj.coord, obj.downside)),
			obj.vec) / inner_pro(ray, obj.vec);
	if (fabs(t) > NEAR_ZERO
		&& in_downcircle(ray, obj, camera, t) && (hit->t == -1.0 || hit->t > t))
		set_hit_cylinder(hit, t, obj, CYL_DOWN);
	return ;
}
