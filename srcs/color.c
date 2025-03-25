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

int	int_color(short red, short green, short blue)
{
	return (red << 16 | green << 8 | blue);
}

void	cal_color(t_hit *hit, t_rgb t, t_a_lighting *amb_light)
{
	double	r;
	double	g;
	double	b;
	t_rgb	amb;

	amb.red = t.red * amb_light->ratio * amb_light->colors.red;
	amb.green = t.green * amb_light->ratio * amb_light->colors.green;
	amb.blue = t.blue * amb_light->ratio * amb_light->colors.blue;
	r = (amb.red + hit->diff.red + hit->spec.red) * 255.0;
	g = (amb.green + hit->diff.green + hit->spec.green) * 255.0;
	b = (amb.blue + hit->diff.blue + hit->spec.blue) * 255.0;
	if (r >= 255)
		r = 255;
	if (g >= 255)
		g = 255;
	if (b >= 255)
		b = 255;
	hit->color
		= int_color((int)round(r), (int)round(g), (int)round(b));
	return ;
}
