/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:38:38 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/08 20:25:11 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_xyz	get_ray(t_mini *mini, double distance, double display_x, double display_y)
{
	t_xyz	toward_dir;
	t_xyz	right_dir;
	t_xyz	up_dir;
	t_xyz	ray_direction;

	toward_dir = vec_multiplied(distance, mini->camera->vec);
	right_dir = vec_multiplied(display_x, mini->right_vec);
	up_dir = vec_multiplied(display_y, mini->up_vec);
	ray_direction = vec_addition(toward_dir, vec_addition(right_dir, up_dir));
	normalize(&ray_direction);
	return (ray_direction);
}

t_xyz	vec_subtraction(t_xyz a, t_xyz b)
{
	return (set_vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_xyz	vec_addition(t_xyz a, t_xyz b)
{
	return (set_vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_xyz	vec_multiplied(double scalar, t_xyz vec)
{
	return (set_vec(vec.x * scalar, vec.y * scalar, vec.z * scalar));
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

t_xyz	cross_product(t_xyz a, t_xyz b)
{
	t_xyz	cross;

	cross.x = a.y * b.z - a.z * b.y + 0.0;
	cross.y = a.z * b.x - a.x * b.z + 0.0;
	cross.z = a.x * b.y - a.y * b.x + 0.0;
	return (cross);
}

double	innner_product(t_xyz a, t_xyz b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_xyz	set_vec(double x, double y, double z)
{
	t_xyz	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
