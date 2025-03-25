#include "../includes/mini_rt.h"

int	shadow_sphere(t_xyz ray, t_sphere obj, t_xyz point, double max)
{
	double	t;
	double	f[4];

	f[A] = pow(vec_norm(ray), 2.0);
	f[B] = 2.0 * (inner_pro(point, ray) - inner_pro(obj.coord, ray));
	f[C] = pow(vec_norm(vec_sub(point, obj.coord)), 2.0)
		- pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	if (f[D] >= NEAR_ZERO)
	{
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t > NEAR_ZERO && t <= max)
			return (1);
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t > NEAR_ZERO && t <= max)
			return (1);
	}
	return (0);
}

int	shadow_plane(t_xyz ray, t_plane obj, t_xyz point, double max)
{
	double	t;
	double	d;

	d = inner_pro(vec_mul(-1.0, ray), obj.vec);
	if (d > NEAR_ZERO)
	{
		t = inner_pro(vec_sub(point, obj.coord), obj.vec) / d;
		if (t > NEAR_ZERO && t <= max)
			return (2);
	}
	return (0);
}

int	shadow_cyl_side(t_xyz ray, t_cylinder obj, t_xyz point, double max)
{
	double	t;
	double	f[4];
	double	h[2];
	t_xyz	ray_dot_objvec;
	t_xyz	cam_center_dot_objvec;

	ray_dot_objvec = vec_sub(ray, vec_mul(inner_pro(ray, obj.vec), obj.vec));
	cam_center_dot_objvec = vec_sub(vec_sub(point, obj.coord),
			vec_mul(inner_pro(vec_sub(point, obj.coord), obj.vec), obj.vec));
	f[A] = pow(vec_norm(ray_dot_objvec), 2.0);
	f[B] = 2 * inner_pro(cam_center_dot_objvec, ray_dot_objvec);
	f[C] = pow(vec_norm(cam_center_dot_objvec), 2.0)
		- pow(obj.diameter / 2.0, 2.0);
	f[D] = pow(f[B], 2.0) - (4.0 * f[A] * f[C]);
	cal_height(obj, point, ray, h);
	if (f[D] >= NEAR_ZERO)
	{
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t > NEAR_ZERO && t <= max && in_height(t, h))
			return (3);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t > NEAR_ZERO && t <= max && in_height(t, h))
			return (3);
	}
	return (0);
}

int	shadow_cyl_surface(t_xyz ray, t_cylinder obj, t_xyz point, double max)
{
	double	t;

	if (fabs(inner_pro(ray, obj.vec)) <= NEAR_ZERO)
		return (0);
	t = -inner_pro(vec_sub(point, vec_add(obj.coord, obj.upside)),
			obj.vec) / inner_pro(ray, obj.vec);
	if (t > NEAR_ZERO && in_upcircle(ray, obj, point, t) && t <= max)
		return (4);
	t = -inner_pro(vec_sub(point, vec_add(obj.coord, obj.downside)),
			obj.vec) / inner_pro(ray, obj.vec);
	if (t > NEAR_ZERO && in_downcircle(ray, obj, point, t) && t <= max)
		return (4);
	return (0);
}