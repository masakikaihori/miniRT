/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:50:47 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/19 17:23:35 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_xyz	cylinder_normal_vec(t_hit *hit, t_cylinder obj)
{
	double	t;
	t_xyz	normal_vec;

	t = innner_product(vec_subtraction(hit->intersection, obj.coord), obj.vec);
	normal_vec = vec_subtraction(hit->intersection, vec_multiplied(t, obj.vec));
	return (normal_vec);
}

void	sphere_light(t_xyz ray, t_mini *mini, t_hit *hit, t_sphere obj)
{
	t_xyz	light;
	t_xyz	normal_vec;
	t_xyz	light_vec;
	t_xyz	reflight_vec;

	light = mini->light->coord;
	normal_vec = vec_subtraction(hit->intersection, obj.coord);
	light_vec = vec_subtraction(light, hit->intersection);
	normalize(&normal_vec);
	normalize(&light_vec);
	if (innner_product(normal_vec, light_vec) > NEAR_ZERO)
		hit->diff = mini->light->ratio * innner_product(normal_vec, light_vec);
	reflight_vec = vec_subtraction(vec_multiplied(2 * innner_product(normal_vec, light_vec), normal_vec), light_vec);
	if (innner_product(reflight_vec, vec_multiplied(-1.0, ray)) > NEAR_ZERO)
		hit->spec = SPE_REF * mini->light->ratio * pow(innner_product(reflight_vec, vec_multiplied(-1.0, ray)), SHINE);
	return ;
}

void	plane_light(t_xyz ray, t_mini *mini, t_hit *hit, t_plane obj)
{
	t_xyz	light;
	t_xyz	normal_vec;
	t_xyz	light_vec;
	t_xyz	reflight_vec;

	light = mini->light->coord;
	normal_vec = obj.vec;
	light_vec = vec_subtraction(light, hit->intersection);
	normalize(&normal_vec);
	normalize(&light_vec);
	if (innner_product(normal_vec, light_vec) > NEAR_ZERO)
		hit->diff = mini->light->ratio * innner_product(normal_vec, light_vec);
	reflight_vec = vec_subtraction(vec_multiplied(2 * innner_product(normal_vec, light_vec), normal_vec), light_vec);
	if (innner_product(reflight_vec, vec_multiplied(-1.0, ray)) > NEAR_ZERO)
		hit->spec = SPE_REF * mini->light->ratio * pow(innner_product(reflight_vec, vec_multiplied(-1.0, ray)), SHINE);
	return ;
}

void	cylinder_light(t_xyz ray, t_mini *mini, t_hit *hit, t_cylinder obj)
{
	t_xyz	light;
	t_xyz	normal_vec;
	t_xyz	light_vec;
	t_xyz	reflight_vec;

	light = mini->light->coord;
	if (hit->cylinder == CYL_UP)
		normal_vec = obj.vec;
	else if (hit->cylinder == CYL_DOWN)
		normal_vec = vec_multiplied(-1.0, obj.vec);
	else
		normal_vec = cylinder_normal_vec(hit, obj);
	light_vec = vec_subtraction(light, hit->intersection);
	normalize(&normal_vec);
	normalize(&light_vec);
	if (innner_product(normal_vec, light_vec) < 0)
		normal_vec = vec_multiplied(-1.0, normal_vec);
	if (innner_product(normal_vec, light_vec) > NEAR_ZERO)
		hit->diff = mini->light->ratio * innner_product(normal_vec, light_vec);
	reflight_vec = vec_subtraction(vec_multiplied(2 * innner_product(normal_vec, light_vec), normal_vec), light_vec);
	if (innner_product(reflight_vec, vec_multiplied(-1.0, ray)) > NEAR_ZERO)
		hit->spec = SPE_REF * mini->light->ratio * pow(innner_product(reflight_vec, vec_multiplied(-1.0, ray)), SHINE);
	return ;
}
