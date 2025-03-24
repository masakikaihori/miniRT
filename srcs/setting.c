/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:40:02 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 16:07:57 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	add_light(t_mini *mini, t_light *new)
{
	t_light	*tmp;

	tmp = mini->light;
	if (tmp == NULL)
		mini->light = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
}

void	set_amb(t_mini *mini, char **strs)
{
	if (mini->a_lighting)
		print_frees_exit(mini,
			"ambient_lightning is declared more than once\n", -1, strs);
	mini->a_lighting = (t_a_lighting *)malloc(sizeof(t_a_lighting));
	if (!mini->a_lighting)
		print_frees_exit(mini, NULL, errno, strs);
	if (rt_strslen(strs) != AMB_ELE)
		print_frees_exit(mini,
			"ambient_lightning amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "ambient lightning character\n", -1, strs);
	mini->a_lighting->ratio = rt_atof(mini, strs, strs[1], NULL);
	if (mini->a_lighting->ratio > 1.0 || mini->a_lighting->ratio < 0.0)
		print_frees_exit(mini,
			"ambient_lightning ratio is out of range\n", -1, strs);
	mini->a_lighting->colors = set_rgb(mini, strs, strs[2]);
	return ;
}

void	set_camera(t_mini *mini, char **strs)
{
	if (mini->camera)
		print_frees_exit(mini, "camera is declared more than once\n", -1, strs);
	mini->camera = (t_camera *)malloc(sizeof(t_camera));
	if (!mini->camera)
		print_frees_exit(mini, NULL, errno, strs);
	if (rt_strslen(strs) != CAM_ELE)
		print_frees_exit(mini,
			"camera amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "camera character\n", -1, strs);
	mini->camera->coord = set_xyz(mini, strs, strs[1], 0);
	mini->camera->vec = set_xyz(mini, strs, strs[2], 1);
	if (!vec_range(mini->camera->vec))
		print_frees_exit(mini, "camera vec is out of range\n", -1, strs);
	normalize(&(mini->camera->vec));
	mini->camera->hfov = (double)rt_atos(mini, strs, strs[3], NULL);
	if (mini->camera->hfov > HFOV_MAX)
		print_frees_exit(mini, "camera hfov is out of range\n", -1, strs);
	mini->camera->hfov = mini->camera->hfov / 180 * M_PI;
	mini->camera->vfov = (2 * atan(tan((mini->camera->hfov) / 2)
				/ (WIDTH / HEIGHT)));
	mini->distance = WIDTH / 2.0 / tan(mini->camera->hfov / 2.0);
	mini->x_pixel = tan(mini->camera->hfov / 2.0);
	mini->y_pixel = tan(mini->camera->vfov / 2.0);
	return ;
}

void	set_light(t_mini *mini, char **strs)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		print_frees_exit(mini, NULL, errno, strs);
	light->next = NULL;
	add_light(mini, light);
	if (rt_strslen(strs) != LIG_ELE)
		print_frees_exit(mini, "light amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "light character\n", -1, strs);
	light->coord = set_xyz(mini, strs, strs[1], 0);
	light->ratio = rt_atof(mini, strs, strs[2], NULL);
	if (light->ratio > 1.0 || light->ratio < 0.0)
		print_frees_exit(mini, "light ratio is out of range\n", -1, strs);
	light->colors = set_rgb(mini, strs, strs[3]);
	return ;
}

void	set_screen(t_mini *mini)
{
	if (mini->camera->vec.x == 0 && mini->camera->vec.z == 0)
		mini->camera->vec.z = 0.000001;
	mini->right_vec = cross_pro(mini->world_up, mini->camera->vec);
	mini->up_vec = cross_pro(mini->camera->vec, mini->right_vec);
	normalize(&(mini->right_vec));
	normalize(&(mini->up_vec));
	return ;
}
