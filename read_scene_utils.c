/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:52:09 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/11 18:24:01 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/mini_rt.h"

void	free_strs(char **strs)
{
	int	index;

	if (strs)
	{
		index = 0;
		while (strs[index])
		{
			free(strs[index]);
			index++;
		}
		free(strs);
	}
	return ;
}

int	rt_strslen(char **strs)
{
	int	size;

	size = 0;
	if (!strs)
		return (0);
	while (strs[size])
		size++;
	return (size);
}

short	rt_atos(t_mini *mini, char **strs, char *str, int *index)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		if (num > COLOR_MAX)
		{
			free_strs(strs);
			print_free_exit(mini, "color range over\n", -1);
		}
		i++;
	}
	if (i == 0 || (str[i] != '\0' && str[i] != ','))
	{
		free_strs(strs);
		print_free_exit(mini, "color element\n", -1);
	}
	if (index)
		*index += i; 
	return ((short)num);
}
