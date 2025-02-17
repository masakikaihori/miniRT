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

bool	vec_range(t_xyz vec)
{
	if (vec.x <= 1 && vec.y >= -1 && vec.y <= 1 && vec.y >= -1
		&& vec.z <= 1 && vec.z >= -1)
		return (true);
	return (false);
}

bool	inrange(float num, float min, float max)
{
	if (num > max || num < min)
		return (false);
	return (true);
}

t_xyz	set_xyz(t_mini *mini, char **strs, char *str)
{
	int		index;
	t_xyz	new;

	index = 0;
	new.x = rt_atof(mini, strs, str, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "xyz element error1\n", -1, strs);
	new.y = rt_atof(mini, strs, str + index, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "xyz element error2\n", -1, strs);
	new.z = rt_atof(mini, strs, str + index, &index);
	if (str[index] != '\0')
		print_frees_exit(mini, "xyz element error2\n", -1, strs);
	return (new);
}

t_rgb	set_rgb(t_mini *mini, char **strs, char *str)
{
	int		index;
	t_rgb	new;

	index = 0;
	new.red = rt_atos(mini, strs, str, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "color element1\n", -1, strs);
	new.green = rt_atos(mini, strs, str + index, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "color element2\n", -1, strs);
	new.blue = rt_atos(mini, strs, str + index, &index);
	if (str[index] != '\0')
		print_frees_exit(mini, "color element3\n", -1, strs);
	return (new);
}

bool	not_available(char **strs)
{
	int		i;
	int		j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (!ft_strchr(OK_CHARSET, strs[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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
	if (!inrange(mini->a_lightning->ratio, 0.0, 1.0))
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
	if (!inrange(mini->light->ratio, 0.0, 1.0))
		print_frees_exit(mini, "light ratio is out of range\n", -1, strs);
	mini->light->color = set_rgb(mini, strs, strs[3]);
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
	obj->info.sphere.color = set_rgb(mini, strs, strs[3]);
	return ;
}
