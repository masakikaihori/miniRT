/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:50:47 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 17:37:02 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	cal_reflection(t_xyz xyz[4], t_hit *hit, t_light *tmp_light, t_xyz ray)
{
	double	diff;
	double	spec;

	diff = DIF_REF * tmp_light->ratio
		* inner_pro(xyz[V_NORMAL], xyz[V_LIGHT]);
	xyz[V_REFLIGHT] = reflection_vec(xyz[V_NORMAL], xyz[V_LIGHT]);
	if (inner_pro(xyz[V_REFLIGHT], vec_mul(-1.0, ray)) > NEAR_ZERO)
		spec = spec_light(tmp_light->ratio, xyz[V_REFLIGHT], ray);
	hit->diff.red += diff * tmp_light->colors.red * hit->colors.red;
	hit->diff.green += diff * tmp_light->colors.green * hit->colors.green;
	hit->diff.blue += diff * tmp_light->colors.blue * hit->colors.blue;
	hit->spec.red += spec * tmp_light->colors.red;
	hit->spec.green += spec * tmp_light->colors.green;
	hit->spec.blue += spec * tmp_light->colors.blue;
	return ;
}

void	sphere_light(t_xyz ray, t_light *light, t_hit *hit, t_sphere obj)
{
	t_xyz	xyz[4];
	t_light	*tmp_light;
	int		light_num;

	light_num = LIGHT_BITS;
	tmp_light = light;
	xyz[V_NORMAL] = vec_sub(hit->intersection, obj.coord);
	normalize(&xyz[V_NORMAL]);
	while (hit->lights)
	{
		if (hit->lights >= light_num)
		{
			xyz[P_LIGHT] = tmp_light->coord;
			xyz[V_LIGHT] = vec_sub(xyz[P_LIGHT], hit->intersection);
			normalize(&xyz[V_LIGHT]);
			if (inner_pro(xyz[V_NORMAL], xyz[V_LIGHT]) > NEAR_ZERO)
				cal_reflection(xyz, hit, tmp_light, ray);
			hit->lights -= light_num;
		}
		light_num /= 2;
		tmp_light = tmp_light->next;
	}
	return ;
}

void	plane_light(t_xyz ray, t_light *light, t_hit *hit, t_plane obj)
{
	t_xyz	xyz[4];
	t_light	*tmp_light;
	int		light_num;

	light_num = LIGHT_BITS;
	tmp_light = light;
	xyz[V_NORMAL] = obj.vec;
	normalize(&xyz[V_NORMAL]);
	while (hit->lights)
	{
		if (hit->lights >= light_num)
		{
			xyz[P_LIGHT] = tmp_light->coord;
			xyz[V_LIGHT] = vec_sub(xyz[P_LIGHT], hit->intersection);
			normalize(&xyz[V_LIGHT]);
			if (inner_pro(xyz[V_NORMAL], xyz[V_LIGHT] ) > NEAR_ZERO)
				cal_reflection(xyz, hit, tmp_light, ray);
			hit->lights -= light_num;
		}
		light_num /= 2;
		tmp_light = tmp_light->next;
	}
	return ;
}

void	cylinder_light(t_xyz ray, t_light *light, t_hit *hit, t_cylinder obj)
{
	t_xyz	xyz[4];
	t_light	*tmp_light;
	int		light_num;

	light_num = LIGHT_BITS;
	tmp_light = light;
	xyz[V_NORMAL] = cylinder_normal_vec(hit, obj);
	normalize(&xyz[V_NORMAL]);
	while (hit->lights)
	{
		if (hit->lights >= light_num)
		{
			xyz[P_LIGHT] = tmp_light->coord;
			xyz[V_LIGHT] = vec_sub(xyz[P_LIGHT], hit->intersection);
			normalize(&xyz[V_LIGHT]);
			if (inner_pro(xyz[V_NORMAL], xyz[V_LIGHT] ) > NEAR_ZERO)
				cal_reflection(xyz, hit, tmp_light, ray);
			hit->lights -= light_num;
		}
		light_num /= 2;
		tmp_light = tmp_light->next;
	}
	return ;
}
