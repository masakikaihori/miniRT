/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:38:38 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/23 14:56:55 by mkaihori         ###   ########.fr       */
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
	ray_direction = vec_add(toward_dir, vec_add(right_dir, up_dir));
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

bool	vec_range(t_xyz vec)
{
	if (vec.x <= 1 && vec.y >= -1 && vec.y <= 1 && vec.y >= -1
		&& vec.z <= 1 && vec.z >= -1)
		return (true);
	return (false);
}
