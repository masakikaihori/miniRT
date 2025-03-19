/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:38:38 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/19 18:42:48 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_xyz	get_ray(
		t_mini *mini, double distance, double display_x, double display_y)
{
	t_xyz	toward_dir;
	t_xyz	right_dir;
	t_xyz	up_dir;
	t_xyz	ray_direction;

	toward_dir = vec_mul(distance, mini->camera->vec);
	right_dir = vec_mul(display_x, mini->right_vec);
	up_dir = vec_mul(display_y, mini->up_vec);
	ray_direction = vec_addition(toward_dir, vec_addition(right_dir, up_dir));
	normalize(&ray_direction);
	return (ray_direction);
}

double	vec_norm(t_xyz a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

void	normalize(t_xyz *a)
{
	double	norm;

	norm = vec_norm(*a);
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
	return ;
}

t_xyz	set_vec(double x, double y, double z)
{
	t_xyz	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
