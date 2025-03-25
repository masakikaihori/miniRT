/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:31:21 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 15:33:26 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int	shadow_objects(t_xyz ray, t_object *obj, t_xyz point, double max)
{
	int	sign;

	sign = 0;
	if (obj->type == SPHERE)
		sign = shadow_sphere(ray, obj->info.sphere, point, max);
	else if (obj->type == PLANE)
		sign = shadow_plane(ray, obj->info.plane, point, max);
	else if (obj->type == CYLINDER)
		sign = shadow_cyl_side(ray, obj->info.cylinder, point, max);
	if (obj->type == CYLINDER && !sign)
		sign = shadow_cyl_surface(ray, obj->info.cylinder, point, max);
	return (sign);
}

int	not_shadow(t_object *objs, t_light *light, t_xyz point, t_hit *hit)
{
	t_object	*tmp_obj;
	t_light		*tmp_light;
	t_xyz		ray;
	double		max;
	int			sign;

	tmp_light = light;
	while (tmp_light)
	{
		tmp_obj = objs;
		ray = vec_sub(tmp_light->coord, point);
		max = vec_norm(ray);
		normalize(&ray);
		sign = 0;
		while (tmp_obj && !sign)
		{
			sign = shadow_objects(ray, tmp_obj, point, max);
			tmp_obj = tmp_obj->next;
		}
		if (!sign)
			hit->lights += tmp_light->index;
		tmp_light = tmp_light->next;
	}
	return (hit->lights);
}
