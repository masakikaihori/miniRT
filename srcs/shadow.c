/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:31:21 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/12 19:56:44 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

bool	shadow_sphere(t_xyz ray, t_sphere obj, t_xyz camera, double max)
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
		if (t > 1e-9 && t <= max)
			return (true);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t > 1e-9 && t <= max)
			return (true);
	}
	return (false);
}

bool	shadow_plane(t_xyz ray, t_plane obj, t_xyz camera, double max, int y)
{
	double	t;
	double	d;
(void)y;
	d = innner_product(vec_multiplied(-1.0, ray), obj.vec);
	if (d != 0.0)
	{
		t = innner_product(vec_subtraction(camera, obj.coord), obj.vec) / d;
		if (t > 1e-9 && t <= max)
		{
			return (true);
		}
	}
	return (false);
}

bool	shadow_cylinder_side(t_xyz ray, t_cylinder obj, t_xyz camera, double max)
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
		if (t > 1e-9 && t <= max && in_height(t, h))
			return (true);
		t = (-f[B] - sqrt(f[D])) / (2.0 * f[A]);
		if (t > 1e-9 && t <= max && in_height(t, h))
			return (true);
	}
	return (false);
}

bool	shadow_cylinder_surface(t_xyz ray, t_cylinder obj, t_xyz camera, double max)
{
	double	t;

	if (innner_product(ray, obj.vec) == 0)
		return (false);
	t = -innner_product(vec_subtraction(camera, vec_addition(obj.coord, obj.upside)), obj.vec) / innner_product(ray, obj.vec);
	if (t > 1e-9 && in_upcircle(ray, obj, camera, t) && t <= max)
		return (true);
	t = -innner_product(vec_subtraction(camera, vec_addition(obj.coord, obj.downside)), obj.vec) / innner_product(ray, obj.vec);
	if (t > 1e-9 && in_downcircle(ray, obj, camera, t) && t <= max)
		return (true);
	return (false);
}

bool	is_shadow(t_object *head, t_xyz light, t_xyz point, int y)
{
	t_object	*tmp_obj;
	t_xyz		ray;
	bool		hit;
	double		max;

	tmp_obj = head;
	hit = false;
	ray = vec_subtraction(light, point);
	max = vec_norm(ray);
	normalize(&ray);
	while (tmp_obj && !hit)
	{
		if (tmp_obj->type == SPHERE)
			hit = shadow_sphere(ray, tmp_obj->info.sphere, point, max);
		else if (tmp_obj->type == PLANE)
			hit = shadow_plane(ray, tmp_obj->info.plane, point, max, y);
		else if (tmp_obj->type == CYLINDER)
		{
			hit = shadow_cylinder_side(ray, tmp_obj->info.cylinder, point, max);
			hit = shadow_cylinder_surface(ray, tmp_obj->info.cylinder, point, max);
		}
		tmp_obj = tmp_obj->next;
	}
	return (hit);
}
