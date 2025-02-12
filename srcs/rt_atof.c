/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:16:15 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/11 21:38:33 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

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
	if (str[i] != '\0' && str[i] != 'e' && str[i] != 'E')
	{
		free_strs(strs);
		print_free_exit(mini, "atof error2\n", -1);
	}
	*index = i;
	return (num);
}

int	rt_atof_e(t_mini *mini, char **strs, char *str, int *index)
{
	int	i;
	int	sign;
	int	num;

	i = *index;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	else if (str[i] == 'e' || str[i] == 'E')
		i++;
	else
		print_frees_exit(mini, "atof error\n", -1, strs);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	num = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		print_frees_exit(mini, "atof error\n", -1, strs);
	*index = i;
	return (num * sign);
}

float	rt_atof(t_mini *mini, char **strs, char *str, int *index)
{
	float	num;
	int		i;
	int		sign;

	num = 0.0;
	i = 0;
	sign = 1;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		num = num * 10.0 + str[i++] - '0';
	if ((i == 0 && str[i] != '.')
		|| (str[i] != '\0' && str[i] != '.' && str[i] != 'e' && str[i] != 'E'))
		print_frees_exit(mini, "atof error\n", -1, strs);
	num += rt_atof_util(mini, strs, str, &i);
	num = num * pow(10.0, (double)rt_atof_e(mini, strs, str, &i));
	if (isinf(num))
		print_frees_exit(mini, "atof inf\n", -1, strs);
	if (index)
		*index += i;
	return (num * sign);
}
