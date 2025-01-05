/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:17:02 by mkaihori          #+#    #+#             */
/*   Updated: 2024/12/30 18:17:07 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini) * 1);
	if (!mini)
		print_free_exit(mini, NULL, errno);
	mini->mlx = NULL;
	mini->win = NULL;
	mini->object = NULL;
	mini->status = EXIT_SUCCESS;
	return (mini);
}

int	deal_key(int key, void *param)
{
	t_mini	*mini;

	mini = (t_mini *)param;
	if (key == 65307)
		free_exit(mini, 0);
	printf("%d\n", key);
	return (mini->status);
}

int	main(int ac, char *av[])
{
	t_mini	*mini;

	errno = 0;
	if (ac != 2)
		print_free_exit(NULL, "need a scene in format *.rt\n", -1);
	mini = init_mini();
	mini->object = read_scene(mini, av[1]);
	mini->mlx = mlx_init();
	if (!mini->mlx)
		print_free_exit(mini, "mlx_init_error\n", -1);
	mini->win = mlx_new_window(mini->mlx, 500, 500, "miniRT");
	mlx_key_hook(mini->win, deal_key, mini);
	mlx_hook(mini->win, 17, 0, free_exit, mini);
	mlx_loop(mini->mlx);
	return (0);
}
