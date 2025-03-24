/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:50:47 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 14:52:33 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	sphere_light(t_xyz ray, t_mini *mini, t_hit *hit, t_sphere obj)
{
	t_xyz	light;
	t_xyz	normal_vec;
	t_xyz	light_vec;
	t_xyz	reflight_vec;

	light = mini->light->coord;
	normal_vec = vec_sub(hit->intersection, obj.coord);
	light_vec = vec_sub(light, hit->intersection);
	normalize(&normal_vec);
	normalize(&light_vec);
	if (inner_pro(normal_vec, light_vec) > NEAR_ZERO)
	{
		hit->diff = mini->light->ratio * inner_pro(normal_vec, light_vec);
		reflight_vec = reflection_vec(normal_vec, light_vec);
		if (inner_pro(reflight_vec, vec_mul(-1.0, ray)) > NEAR_ZERO)
			hit->spec = spec_light(mini->light->ratio, reflight_vec, ray);
	}
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
	light_vec = vec_sub(light, hit->intersection);
	normalize(&normal_vec);
	normalize(&light_vec);
	if (inner_pro(normal_vec, light_vec) > NEAR_ZERO)
	{
		hit->diff = mini->light->ratio * inner_pro(normal_vec, light_vec);
		reflight_vec = reflection_vec(normal_vec, light_vec);
		if (inner_pro(reflight_vec, vec_mul(-1.0, ray)) > NEAR_ZERO)
			hit->spec = spec_light(mini->light->ratio, reflight_vec, ray);
	}
	return ;
}

void	cylinder_light(t_xyz ray, t_mini *mini, t_hit *hit, t_cylinder obj, int y)
{
	t_xyz	light;
	t_xyz	normal_vec;
	t_xyz	light_vec;
	t_xyz	reflight_vec;
(void)y;
	light = mini->light->coord;
	if (hit->cylinder == CYL_UP)
		normal_vec = obj.vec;
	else if (hit->cylinder == CYL_DOWN)
		normal_vec = vec_mul(-1.0, obj.vec);
	else
		normal_vec = cylinder_normal_vec(hit, obj);
	light_vec = vec_sub(light, hit->intersection);
	normalize(&normal_vec);
	normalize(&light_vec);
	if (inner_pro(normal_vec, light_vec) > NEAR_ZERO)
	{
		hit->diff = mini->light->ratio * inner_pro(normal_vec, light_vec);
		reflight_vec = reflection_vec(normal_vec, light_vec);
		if (inner_pro(reflight_vec, vec_mul(-1.0, ray)) > NEAR_ZERO)
			hit->spec = spec_light(mini->light->ratio, reflight_vec, ray);
	}
	return ;
}
