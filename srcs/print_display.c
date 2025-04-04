/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:44:27 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 17:37:39 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_object	*obj_ptr_index(t_object *head, int index)
{
	t_object	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->index == index)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_xyz	intersection_pos(t_xyz camera, double t, t_xyz ray)
{
	return (vec_add(camera, vec_mul(t, ray)));
}

void	cal_light(t_xyz ray, t_mini *mini, t_hit *hit)
{
	t_object	*obj;

	if (hit->t == -1)
	{
		hit->color = int_color(0, 0, 0);
		return ;
	}
	hit->lights = 0;
	hit->intersection = intersection_pos(mini->camera->coord, hit->t, ray);
	obj = obj_ptr_index(mini->object, hit->index);
	ft_bzero(&(hit->diff), sizeof(hit->diff));
	ft_bzero(&(hit->spec), sizeof(hit->spec));
	if (not_shadow(mini->object, mini->light, hit->intersection, hit))
	{
		if (obj->type == SPHERE)
			sphere_light(ray, mini->light, hit, obj->info.sphere);
		else if (obj->type == PLANE)
			plane_light(ray, mini->light, hit, obj->info.plane);
		else if (obj->type == CYLINDER)
			cylinder_light(ray, mini->light, hit, obj->info.cylinder);
	}
	cal_color(hit, hit->colors, mini->a_lighting);
	return ;
}

void	expand_ray(t_mini *mini, t_xyz ray, int x, int y)
{
	t_object	*tmp_obj;
	t_hit		hit;
	t_xyz		camera_pos;

	tmp_obj = mini->object;
	hit.t = -1;
	camera_pos = mini->camera->coord;
	while (tmp_obj)
	{
		if (tmp_obj->type == SPHERE)
			ray_sphere(ray, tmp_obj->info.sphere, &hit, camera_pos);
		else if (tmp_obj->type == PLANE)
			ray_plane(ray, tmp_obj->info.plane, &hit, camera_pos);
		else if (tmp_obj->type == CYLINDER)
		{
			ray_cyl_side(ray, tmp_obj->info.cylinder, &hit, camera_pos);
			ray_cyl_surface(ray, tmp_obj->info.cylinder, &hit, camera_pos);
		}
		tmp_obj = tmp_obj->next;
	}
	cal_light(ray, mini, &hit);
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
