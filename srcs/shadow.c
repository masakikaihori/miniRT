/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:31:21 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/19 19:22:45 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

bool	shadow_sphere(t_xyz ray, t_sphere obj, t_xyz point, double max)
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
			return (true);
		t = (-f[B] + sqrt(f[D])) / (2.0 * f[A]);
		if (t > NEAR_ZERO && t <= max)
			return (true);
	}
	return (false);
}

bool	shadow_plane(t_xyz ray, t_plane obj, t_xyz point, double max)
{
	double	t;
	double	d;

	d = inner_pro(vec_mul(-1.0, ray), obj.vec);
	if (d > NEAR_ZERO)
	{
		t = inner_pro(vec_sub(point, obj.coord), obj.vec) / d;
		if (t > NEAR_ZERO && t <= max)
			return (true);
	}
	return (false);
}

bool	shadow_cyl_side(t_xyz ray, t_cylinder obj, t_xyz point, double max)
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
			return (true);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t > NEAR_ZERO && t <= max && in_height(t, h))
			return (true);
	}
	return (false);
}

bool	shadow_cyl_surface(t_xyz ray, t_cylinder obj, t_xyz point, double max)
{
	double	t;

	if (inner_pro(ray, obj.vec) >= NEAR_ZERO)
		return (false);
	t = -inner_pro(vec_sub(point, vec_addition(obj.coord, obj.upside)),
			obj.vec) / inner_pro(ray, obj.vec);
	if (t > NEAR_ZERO && in_upcircle(ray, obj, point, t) && t <= max)
		return (true);
	t = -inner_pro(vec_sub(point, vec_addition(obj.coord, obj.downside)),
			obj.vec) / inner_pro(ray, obj.vec);
	if (t > NEAR_ZERO && in_downcircle(ray, obj, point, t) && t <= max)
		return (true);
	return (false);
}

bool	is_shadow(t_object *head, t_xyz light, t_xyz point)
{
	t_object	*tmp_obj;
	t_xyz		ray;
	bool		hit;
	double		max;

	tmp_obj = head;
	hit = false;
	ray = vec_sub(light, point);
	max = vec_norm(ray);
	normalize(&ray);
	while (tmp_obj && !hit)
	{
		if (tmp_obj->type == SPHERE)
			hit = shadow_sphere(ray, tmp_obj->info.sphere, point, max);
		else if (tmp_obj->type == PLANE)
			hit = shadow_plane(ray, tmp_obj->info.plane, point, max);
		else if (tmp_obj->type == CYLINDER)
		{
			hit = shadow_cyl_side(ray, tmp_obj->info.cylinder, point, max);
			if (!hit)
				hit = shadow_cyl_surface(ray, tmp_obj->info.cylinder, point, max);
		}
		tmp_obj = tmp_obj->next;
	}
	return (hit);
}