/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:44:59 by mkaihori          #+#    #+#             */
/*   Updated: 2025/04/19 01:05:32 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int	open_rtfile(t_mini *mini, char *file)
{
	int	i;
	int	fd;

	i = 0;
	while (file[i])
		i++;
	if (i <= 3)
		print_free_exit(mini, "not *.rt file\n", -1);
	if (file[--i] == 't' && file[--i] == 'r' && file[--i] == '.')
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			print_free_exit(mini, NULL, errno);
		return (fd);
	}
	else
		print_free_exit(mini, "not *.rt file\n", -1);
	return (-1);
}

t_otype	get_identifer(char *str)
{
	size_t	str_size;

	str_size = ft_strlen(str);
	if (str_size == 1 && ft_strncmp(str, "A", str_size + 1) == 0)
		return (AMBIENT_LIGHTNING);
	else if (str_size == 1 && ft_strncmp(str, "C", str_size + 1) == 0)
		return (CAMERA);
	else if (str_size == 1 && ft_strncmp(str, "L", str_size + 1) == 0)
		return (LIGHT);
	else if (str_size == 2 && ft_strncmp(str, "sp", str_size + 1) == 0)
		return (SPHERE);
	else if (str_size == 2 && ft_strncmp(str, "pl", str_size + 1) == 0)
		return (PLANE);
	else if (str_size == 2 && ft_strncmp(str, "cy", str_size + 1) == 0)
		return (CYLINDER);
	return (UNKNOWN);
}

void	parse_strs(t_mini *mini, char **strs)
{
	t_otype			indentifer;

	indentifer = get_identifer(strs[0]);
	if (indentifer == UNKNOWN)
		print_frees_exit(mini, "identifer is not available\n", -1, strs);
	else if (indentifer == AMBIENT_LIGHTNING)
		set_amb(mini, strs);
	else if (indentifer == CAMERA)
		set_camera(mini, strs);
	else if (indentifer == LIGHT)
		set_light(mini, strs);
	else if (indentifer == SPHERE)
		set_sphere(mini, strs);
	else if (indentifer == PLANE)
		set_plane(mini, strs);
	else if (indentifer == CYLINDER)
		set_cylinder(mini, strs);
	return ;
}

void	read_scene(t_mini *mini, char *file)
{
	char		*str;
	char		**strs;

	mini->fd = open_rtfile(mini, file);
	str = get_next_line(mini->fd);
	while (str)
	{
		strs = rt_split(mini, str);
		if (strs)
		{
			parse_strs(mini, strs);
			free_strs(strs);
		}
		str = get_next_line(mini->fd);
	}
	if (!mini->camera)
		print_free_exit(mini, "no camera\n", -1);
	if (!mini->a_lighting)
		print_free_exit(mini, "no ambient lighting\n", -1);
	if (!mini->light)
		print_free_exit(mini, "no light\n", -1);
	rt_close(mini);
	return ;
}
