/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:40:02 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/13 19:56:57 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_xyz	set_xyz(t_mini *mini, char **strs, char *str)
{
	int		index;
	t_xyz	new;

	index = 0;
	new.x = rt_atof(mini, strs, str, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "xyz element error1\n", -1, strs);
	new.y = rt_atof(mini, strs, str + index, &index);
	if (strs[index++] == '\0')
	print_frees_exit(mini, "xyz element error2\n", -1, strs);
	new.z = rt_atof(mini, strs, str + index, &index);
	return (new);
}

t_rgb	set_rgb(t_mini *mini, char **strs, char *str)
{
	int	index;
	t_rgb new;

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
			if(!ft_strchr(OK_CHARSET, strs[i][j]))
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
		print_frees_exit(mini, "ambient_lighting is declared more than once\n", -1, strs);
	mini->a_lightning = (t_a_lightning *)malloc(sizeof(t_a_lightning));
	if (!mini->a_lightning)
		print_frees_exit(mini, NULL, errno, strs);
	if (rt_strslen(strs) != AMB_ELE)
		print_frees_exit(mini, "ambient_lighting amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "ambient lighting character\n", -1, strs);
	mini->a_lightning->ratio = rt_atof(mini, strs, strs[1], NULL);
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
		print_frees_exit(mini, "ambient_lighting amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "camera character\n", -1, strs);
	mini->camera->coord = set_xyz(mini, strs, strs[1]);
	mini->camera->vec = set_xyz(mini, strs, strs[2]);
	mini->camera->fov = rt_atos(mini, strs, strs[3], NULL);
	if (mini->camera->fov > FOV_MAX)
		print_frees_exit(mini, "camera fov range error\n", -1, strs);
	return ;
}
