/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:52:09 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/13 19:33:04 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

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
	if (str[0] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		if (num > ATOS_MAX)
			print_frees_exit(mini, "atos range over\n", -1, strs);
		i++;
	}
	if (i == 0 || (str[i] != '\0' && str[i] != ','))
		print_frees_exit(mini, "atos character error\n", -1, strs);
	if (index)
		*index += i;
	return ((short)num);
}

void	rt_close(t_mini *mini)
{
	int	value;

	if (mini->fd)
	{
		value = close(mini->fd);
		mini->fd = 0;
		if (value)
			print_free_exit(mini, NULL, errno);
	}
	return ;
}
