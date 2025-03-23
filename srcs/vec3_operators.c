/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:01:31 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/23 14:56:55 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_xyz	vec_sub(t_xyz a, t_xyz b)
{
	return (set_vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_xyz	vec_add(t_xyz a, t_xyz b)
{
	return (set_vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_xyz	vec_mul(double scalar, t_xyz vec)
{
	return (set_vec(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

t_xyz	cross_pro(t_xyz a, t_xyz b)
{
	t_xyz	cross;

	cross.x = a.y * b.z - a.z * b.y + 0.0;
	cross.y = a.z * b.x - a.x * b.z + 0.0;
	cross.z = a.x * b.y - a.y * b.x + 0.0;
	return (cross);
}

double	inner_pro(t_xyz a, t_xyz b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
