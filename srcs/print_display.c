/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:44:27 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/03 19:21:06 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	print_display(t_mini *mini)
{
	// t_xyz	ray_direction;
	float	display_x;
	float	display_y;
	float	distance;
	int		i = 1;

	display_y = HEIGHT / 2.0;
	set_screen(mini);
	distance = WIDTH / 2.0 / tan(mini->camera->hfov / 2.0);
	while (display_y > -HEIGHT / 2.0)
	{
		display_x = -WIDTH / 2.0;
		while (display_x < WIDTH / 2.0)
		{
			// ray_direction = get_ray(mini, distance, display_x, display_y);
			// printf("%d: %f, %f, %f   ", i, ray_direction.x, ray_direction.y, ray_direction.z);
			printf("%d:%f,%f   ", i, display_x, display_y);
			i++;
			display_x += distance * tan(mini->camera->hfov / 2.0) / (WIDTH / 2);
		}
		display_y -= distance * tan(mini->camera->vfov / 2.0) / (HEIGHT / 2);
	}
	return ;
}

// void	print_display(t_mini *mini)
// {
// 	float	w;
// 	float	h;
// 	float	hfov;
// 	float	vfov;
// 	int		i;
// 	t_xyz	tmp;

// 	w = tan(mini->camera->hfov / 180 * M_PI);
// 	h = tan(mini->camera->vfov / 180 * M_PI);
// 	vfov = mini->camera->vfov;
// 	tmp.x = -w;
// 	tmp.y = h;
// 	tmp.z = 1;
// 	i = 1;
// 	while (tmp.y > -h)
// 	{
// 		hfov = mini->camera->hfov;
// 		tmp.x = -tan(hfov / 180 * M_PI);
// 		while (tmp.x < w)
// 		{
// 			printf("%d:%f,%f   ", i, tmp.x, tmp.y);
// 			i++;
// 			hfov -= mini->camera->hfov/(WIDTH/2.0);
// 			tmp.x = -tan(hfov / 180 * M_PI);
// 		}
// 		vfov -= mini->camera->vfov/(HEIGHT/2.0);
// 		tmp.y = tan(vfov / 180 * M_PI);
// 	}
// 	return ;
// }
