/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:36:55 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/08 16:16:00 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	add_object(t_mini *mini, t_object *new)
{
	t_object	*tmp;

	tmp = mini->object;
	if (tmp == NULL)
		mini->object = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
}

void	set_sphere(t_mini *mini, char **strs)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		print_frees_exit(mini, NULL, errno, strs);
	obj->type = SPHERE;
	obj->next = NULL;
	add_object(mini, obj);
	if (rt_strslen(strs) != SPH_ELE)
		print_frees_exit(mini, "sphere amout of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "sphere character\n", -1, strs);
	obj->info.sphere.coord = set_xyz(mini, strs, strs[1]);
	obj->info.sphere.diameter = rt_atof(mini, strs, strs[2], NULL);
	obj->info.sphere.colors = set_rgb(mini, strs, strs[3]);
	obj->info.sphere.color = int_color(obj->info.sphere.colors.red,
			obj->info.sphere.colors.green, obj->info.sphere.colors.blue);
	return ;
}

void	set_plane(t_mini *mini, char **strs)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		print_frees_exit(mini, NULL, errno, strs);
	obj->type = PLANE;
	obj->next = NULL;
	add_object(mini, obj);
	if (rt_strslen(strs) != PLA_ELE)
		print_frees_exit(mini, "plane amout of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "plane character\n", -1, strs);
	obj->info.plane.coord = set_xyz(mini, strs, strs[1]);
	obj->info.plane.vec = set_xyz(mini, strs, strs[2]);
	if (!vec_range(obj->info.plane.vec))
		print_frees_exit(mini, "plane vec is out of range", -1, strs);
	normalize(&(obj->info.plane.vec));
	obj->info.plane.colors = set_rgb(mini, strs, strs[3]);
	obj->info.plane.color = int_color(obj->info.plane.colors.red,
			obj->info.plane.colors.green, obj->info.plane.colors.blue);
	return ;
}

void	set_cylinder(t_mini *mini, char **strs)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		print_frees_exit(mini, NULL, errno, strs);
	obj->type = CYLINDER;
	obj->next = NULL;
	add_object(mini, obj);
	if (rt_strslen(strs) != CYL_ELE)
		print_frees_exit(mini, "cylinder amout of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "cylinder character\n", -1, strs);
	obj->info.cylinder.coord = set_xyz(mini, strs, strs[1]);
	obj->info.cylinder.vec = set_xyz(mini, strs, strs[2]);
	if (!vec_range(obj->info.cylinder.vec))
		print_frees_exit(mini, "cylinder vec is out of range\n", -1, strs);
	normalize(&(obj->info.cylinder.vec));
	obj->info.cylinder.diameter = rt_atof(mini, strs, strs[3], NULL);
	obj->info.cylinder.height = rt_atof(mini, strs, strs[4], NULL);
	obj->info.cylinder.colors = set_rgb(mini, strs, strs[5]);
	obj->info.cylinder.color = int_color(obj->info.cylinder.colors.red,
			obj->info.cylinder.colors.green, obj->info.cylinder.colors.blue);
	return ;
}
