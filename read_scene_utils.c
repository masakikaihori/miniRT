/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:52:09 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/08 18:10:58 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

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

float	rt_atof_util(t_mini *mini, char **strs, char *str, int *index)
{
	int		i;
	float	num;
	float	base;

	i = *index;
	num = 0.0;
	base = 0.1;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		num += (str[i] - '0') * base;
		base /= 10;
		i++;
	}
	if (str[i] != '\0')
	{
		free_strs(strs);
		print_free_exit(mini, "atof error2\n", -1);
	}
	*index += i;
	return (num);
}

float	rt_atof(t_mini *mini, char **strs, char *str, int *index)
{
	float	num;
	int		i;
	int		sign;

	num = 0.0;
	i = 0;
	sign = 1;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
	{
		i++;
		sign *= -1;
	}
	while (ft_isdigit(str[i]))
	{
		num = num * 10.0 + str[i] - '0';
		i++;
	}
	if (i == 0 || (str[i] != '\0' && str[i] != '.'))
	{
		free_strs(strs);
		print_free_exit(mini, "atof erro1\n", -1);
	}
	num += rt_atof_util(mini, strs, str, &i);
	if (index)
		*index += i;
	return (num * sign);
}
