/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:35:54 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/19 16:35:58 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int	int_color(t_rgb colors)
{
	return (colors.red << 16 | colors.green << 8 | colors.blue);
}

bool	vec_range(t_xyz vec)
{
	if (vec.x <= 1 && vec.y >= -1 && vec.y <= 1 && vec.y >= -1
		&& vec.z <= 1 && vec.z >= -1)
		return (true);
	return (false);
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
		print_frees_exit(mini, "colors element1\n", -1, strs);
	new.green = rt_atos(mini, strs, str + index, &index);
	if (str[index++] == '\0')
		print_frees_exit(mini, "colors element2\n", -1, strs);
	new.blue = rt_atos(mini, strs, str + index, &index);
	if (str[index] != '\0')
		print_frees_exit(mini, "colors element3\n", -1, strs);
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
