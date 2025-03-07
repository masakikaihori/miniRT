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

void	expand_ray(t_mini *mini, t_xyz ray, int x, int y)
{
	t_object	*tmp_obj;
	t_hit		hit;

	tmp_obj = mini->object;
	hit.t = -1;
	while (tmp_obj)
	{
		if (tmp_obj->type == SPHERE)
			ray_sphere(ray, tmp_obj->info.sphere, &hit, mini->camera->coord);
		else if (tmp_obj->type == PLANE)
			ray_plane(ray, tmp_obj->info.plane, &hit, mini->camera->coord);
		// else if (tmp_obj->type == CYLINDER)
		// 	ray_cylinder(ray, tmp_obj->info.cylinder, &hit, mini->camera->coord);
		tmp_obj = tmp_obj->next;
	}
	if (hit.t < 0)
		hit.color = int_color(0, 0, 0);
	mlx_pixel_put(mini->mlx, mini->win, x, y, hit.color);
	return ;
}

void	print_display(t_mini *mini)
{
	t_xyz	ray_direction;
	double	display_x;
	double	display_y;
	int		x;
	int		y;

	display_y = HEIGHT / 2.0;
	set_screen(mini);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		display_x = -WIDTH / 2.0;
		while (x < WIDTH)
		{
			ray_direction = get_ray(mini, mini->distance, display_x, display_y);
			expand_ray(mini, ray_direction, x, y);
			x++;
			display_x += mini->distance * mini->x_pixel / (WIDTH / 2.0);
		}
		y++;
		display_y -= mini->distance * mini->y_pixel / (HEIGHT / 2.0);
	}
	return ;
}

// void	print_display(t_mini *mini)
// {
// 	double	w;
// 	double	h;
// 	double	hfov;
// 	double	vfov;
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
