/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:17:15 by mkaihori          #+#    #+#             */
/*   Updated: 2024/12/30 18:17:16 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

void	print_error(char *str)
{
	write(2, "Error\n", 6);
	if (str)
		write(2, str, ft_strlen(str));
	else
		perror(NULL);
	return ;
}

int	free_exit(t_mini *mini, int status)
{
	if (mini)
	{
		if (mini->win)
			mlx_destroy_window(mini->mlx, mini->win);
		if (mini->mlx)
		{
			mlx_destroy_display(mini->mlx);
			free(mini->mlx);
		}
		free(mini);
	}
	exit(status);
}

void	print_free_exit(t_mini *mini, char *str, int status)
{
	print_error(str);
	free_exit(mini, status);
	return ;
}
