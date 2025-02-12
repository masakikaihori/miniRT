/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:17:15 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/11 16:58:15 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	print_error(char *str)
{
	write(2, "Error\n", 6);
	if (str)
		write(2, str, ft_strlen(str));
	else
		perror(NULL);
	return ;
}

int	free_mini(t_mini *mini)
{
	int	status;

	status = EXIT_SUCCESS;
	if (mini)
	{
		if (mini->win)
			mlx_destroy_window(mini->mlx, mini->win);
		if (mini->mlx)
		{
			mlx_destroy_display(mini->mlx);
			free(mini->mlx);
		}
		status = mini->status;
		free(mini);
	}
	return (status);
}

int	free_exit(t_mini *mini)
{
	exit(free_mini(mini));
}

void	print_free_exit(t_mini *mini, char *str, int status)
{
	print_error(str);
	if (mini)
	{
		mini->status = status;
		exit(free_mini(mini));
	}
	exit(status);
}

void	print_frees_exit(t_mini *mini, char *str, int status, char **strs)
{
	free_strs(strs);
	print_free_exit(mini, str, status);
	return ;
}
