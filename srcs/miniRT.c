/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:17:02 by mkaihori          #+#    #+#             */
/*   Updated: 2025/04/19 01:30:55 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini) * 1);
	if (!mini)
		print_free_exit(mini, NULL, errno);
	mini->mlx = NULL;
	mini->win = NULL;
	mini->a_lighting = NULL;
	mini->camera = NULL;
	mini->light = NULL;
	mini->object = NULL;
	mini->status = EXIT_SUCCESS;
	mini->fd = 0;
	mini->world_up = set_vec(0, 1, 0);
	return (mini);
}

int	deal_key(int key, void *param)
{
	t_mini	*mini;

	mini = (t_mini *)param;
	if (key == ESC_KEY)
		mlx_loop_end(mini->mlx);
	return (mini->status);
}

int	main(int ac, char *av[])
{
	t_mini	*mini;

	errno = 0;
	if (ac != 2)
		print_free_exit(NULL, "need a scene in format *.rt\n", -1);
	mini = init_mini();
	read_scene(mini, av[1]);
	mini->mlx = mlx_init();
	if (!mini->mlx)
		print_free_exit(mini, "error at mlx_init\n", -1);
	mini->win = mlx_new_window(mini->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mini->win)
		print_free_exit(mini, "error at mlx_new_window", -1);
	mlx_key_hook(mini->win, deal_key, mini);
	mlx_hook(mini->win, 17, 0, free_exit, mini);
	print_display(mini);
	mlx_loop(mini->mlx);
	return (free_mini(mini));
}
