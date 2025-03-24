/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:00:54 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 17:23:54 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	cal_color(t_hit *hit, t_rgb t, t_a_lighting *amb, t_light *light)
{
	double	red;
	double	green;
	double	blue;

	red = (t.red / 255.0 * amb->ratio * amb->colors.red / 255.0 + hit->diff * light->colors.red / 255.0 * t.red / 255.0 + hit->spec * light->colors.red) * 255.0;
	green = (t.green / 255.0 * amb->ratio * amb->colors.green / 255.0 + hit->diff * light->colors.green / 255.0 * t.green / 255.0 + hit->spec * light->colors.green) * 255.0;
	blue = (t.blue / 255.0 * amb->ratio * amb->colors.blue / 255.0 + hit->diff * light->colors.blue / 255.0 * t.blue / 255.0 + hit->spec * light->colors.blue) * 255.0;
	if (red >= 255)
	red = 255;
	else if (red < 0)
	red = 0;
	if (green >= 255)
	green = 255;
	else if (green < 0)
	green = 0;
	if (blue >= 255)
	blue = 255;
	else if (blue < 0)
	blue = 0;
	hit->color
		= int_color((int)round(red), (int)round(green), (int)round(blue));
	return ;
}
