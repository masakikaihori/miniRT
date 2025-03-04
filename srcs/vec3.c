/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:38:38 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/03 19:14:00 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

float	vec_norm(t_xyz a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

void	normalize(t_xyz *a)
{
	float	norm;

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

t_xyz	set_vec(float x, float y, float z)
{
	t_xyz	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
