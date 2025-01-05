/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:44:59 by mkaihori          #+#    #+#             */
/*   Updated: 2024/12/30 23:28:33 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

int	open_rtfile(t_mini *mini, char *file)
{
	int	i;
	int	fd;

	i = 0;
	while (file[i])
		i++;
	if (i <= 3)
		return (0);
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

t_objecttype	get_identifer(char *str)
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

t_object	*parse_strs(char **strs)
{
	t_object		*new;
	t_objecttype	indentifer;
	int				index;

	indentifer = get_identifer(strs[0]);
	if (indentifer == UNKNOWN)
		return (NULL);
	new = (t_object *)malloc(sizeof(t_object) * 1);
	if (!new)
		return (NULL);
	index = 0;
	return (new);
}

t_object	*read_scene(t_mini *mini, char *file)
{
	t_object	*head;
	t_object	*new;
	char		*str;
	char		**strs;
	int			fd;

	head = NULL;
	fd = open_rtfile(mini, file);
	str = get_next_line(fd);
	if (str)
	{
		strs = ft_split(str, ' ');
		free(str);
		if (!strs)
			print_free_exit(mini, "not *.rt file\n", -1);
		new = parse_strs(strs);
		free(strs);
		if (!new)
			print_free_exit(mini, "parse error\n", -1);
		ft_lstadd_back(&head, new);
		str = get_next_line(fd);
	}
	return (head);
}
