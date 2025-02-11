/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:40:02 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/11 18:23:48 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/mini_rt.h"

t_rgb	set_color(t_mini *mini, char **strs, char *str)
{
	int	index;
	t_rgb new;

	index = 0;
	new.red = rt_atos(mini, strs, str, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "color element\n", -1, strs);
	str = str + index;
	new.green = rt_atos(mini, strs, str, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "color element\n", -1, str);
	str = str + index;
	new.blue = rt_atos(mini, strs, str, &index);
	if (str[index] != '\0')
		print_frees_exit(mini, "color element\n", -1, strs);
	return (new);
}

bool	not_available(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if(ft_strchr(OK_CHARSET, strs[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_a_lighting	*set_amb(t_mini *mini, char **strs)
{
	t_a_lighting	*new;

	if (mini->object.a_lighting)
		print_frees_exit(mini, "ambient_lighting is declared more than once\n", -1, strs);
	new = (t_a_lighting *)malloc(sizeof(t_a_lighting));
	if (!new)
		print_frees_exit(mini, NULL, errno, strs);
	if (rt_strslen(strs) != AMB_ELE)
		print_frees_exit(mini, "ambient_lighting amount of element\n", -1, strs);
	if (not_available(strs + 1))
		print_frees_exit(mini, "ambient lighting character\n", -1, strs);
	new->ratio = rt_atof(mini, strs, strs[1], NULL);
	new->color = set_color(mini, strs, strs[2]);
	mini->object.a_lighting = new;
	return ;
}

t_camera	*set_camera(t_mini *mini, char **strs)
{
	t_camera	*new;

	if (mini->object.camera)
	{
		free_strs(strs);
		print_free_exit(mini, "camera is declared more than once\n", -1);
	}
	new = (t_camera *)malloc(sizeof(t_camera));
	if (!new)
	{
		free_strs(strs);
		print_free_exit(mini, NULL, errno);
	}
	if (rt_strslen(strs) != CAM_ELE)
	{
		free_strs(strs);
		print_free_exit(mini, "ambient_lighting amount of element\n", -1);
	}
	new->coord = ;
	new->vec = ;
	new->fov = ;
	mini->object.camera = new;
}
