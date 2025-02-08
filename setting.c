/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:40:02 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/08 17:43:08 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

t_rgb	set_color(t_mini *mini, char **strs, char *str)
{
	int	index;
	t_rgb new;

	index = 0;
	new.red = rt_atos(mini, strs, str, &index);
	if (str[index++] == '\0')
	{
		free_strs(strs);
		print_free_exit(mini, "color element\n", -1);
	}
	str = str + index;
	new.green = rt_atos(mini, strs, str, &index);
	if (str[index++] == '\0')
	{
		free_strs(strs);
		print_free_exit(mini, "color element\n", -1);
	}
	str = str + index;
	new.blue = rt_atos(mini, strs, str, &index);
	if (str[index] != '\0')
	{
		free_strs(strs);
		print_free_exit(mini, "color element\n", -1);
	}
	return (new);
}

t_a_lighting	*set_amb(t_mini *mini, char **strs)
{
	t_a_lighting	*new;

	if (mini->object.a_lighting)
	{
		free_strs(strs);
		print_free_exit(mini, "ambient_lighting is declared more than once\n", -1);
	}
	new = (t_a_lighting *)malloc(sizeof(t_a_lighting));
	if (!new)
	{
		free_strs(strs);
		print_free_exit(mini, NULL, errno);
	}
	if (rt_strslen(strs) != AMB_ELE)
	{
		free_strs(strs);
		print_free_exit(mini, "ambient_lighting amount of element\n", -1);
	}
	new->ratio = rt_atof(mini, strs, strs[1]);
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
