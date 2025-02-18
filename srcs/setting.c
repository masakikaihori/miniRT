/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:40:02 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/17 18:26:22 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	set_amb(t_mini *mini, char **strs)
{
	if (mini->a_lightning)
		print_frees_exit(mini,
			"ambient_lightning is declared more than once\n", -1, strs);
	mini->a_lightning = (t_a_lightning *)malloc(sizeof(t_a_lightning));
	if (!mini->a_lightning)
		print_frees_exit(mini, NULL, errno, strs);
	if (rt_strslen(strs) != AMB_ELE)
		print_frees_exit(mini,
			"ambient_lightning amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "ambient lightning character\n", -1, strs);
	mini->a_lightning->ratio = rt_atof(mini, strs, strs[1], NULL);
	if (mini->a_lightning->ratio > 1.0 || mini->a_lightning->ratio < 0.0)
		print_frees_exit(mini,
			"ambient_lightning ratio is out of range\n", -1, strs);
	mini->a_lightning->color = set_rgb(mini, strs, strs[2]);
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
	mini->camera->coord = set_xyz(mini, strs, strs[1]);
	mini->camera->vec = set_xyz(mini, strs, strs[2]);
	if (!vec_range(mini->camera->vec))
		print_frees_exit(mini, "camera vec is out of range\n", -1, strs);
	mini->camera->fov = rt_atos(mini, strs, strs[3], NULL);
	if (mini->camera->fov > FOV_MAX)
		print_frees_exit(mini, "camera fov is out of range\n", -1, strs);
	return ;
}

void	set_light(t_mini *mini, char **strs)
{
	if (mini->light)
		print_frees_exit(mini, "light is declared more than once\n", -1, strs);
	mini->light = (t_light *)malloc(sizeof(t_light));
	if (!mini->light)
		print_frees_exit(mini, NULL, errno, strs);
	if (rt_strslen(strs) != LIG_ELE)
		print_frees_exit(mini, "light amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "light character\n", -1, strs);
	mini->light->coord = set_xyz(mini, strs, strs[1]);
	mini->light->ratio = rt_atof(mini, strs, strs[2], NULL);
	if (mini->light->ratio > 1.0 || mini->light->ratio < 0.0)
		print_frees_exit(mini, "light ratio is out of range\n", -1, strs);
	mini->light->color = set_rgb(mini, strs, strs[3]);
	return ;
}
