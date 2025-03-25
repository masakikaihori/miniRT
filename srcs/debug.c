/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:37:04 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 16:10:39 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	debug_free(void *ptr)
{
	printf("free %p\n", ptr);
	free(ptr);
	return ;
}

void	*debug_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	printf("malloc : %p\n", ptr);
	return (ptr);
}

void	print_xyz(t_xyz xyz, char *str)
{
	printf("%s x : %f\n", str, xyz.x);
	printf("%s y : %f\n", str, xyz.y);
	printf("%s z : %f\n", str, xyz.z);
	return ;
}

void	print_colors(t_rgb colors, char *str)
{
	printf("%s red : %f\n", str, colors.red * 255.0);
	printf("%s green : %f\n", str, colors.green * 255.0);
	printf("%s blue : %f\n", str, colors.blue * 255.0);
}

void	print_mini(t_mini *mini)
{
	t_object	*tmp;
	t_light		*tmp_l;

	tmp = mini->object;
	tmp_l = mini->light;
	printf("-----debug-----\n");
	if (mini)
	{
		if (mini->mlx)
			printf("mlx ptr : %p\n", mini->mlx);
		else
			printf("no mlx ptr\n");
		printf("\n");
		if (mini->win)
			printf("win ptr : %p\n", mini->win);
		else
			printf("no win ptr\n");
		printf("\n");
		if (mini->a_lighting)
		{
			printf("a_lighting ptr : %p\n", mini->a_lighting);
			printf("a_lighting ratio : %f\n", mini->a_lighting->ratio);
			print_colors(mini->a_lighting->colors, "a_lighting colors");
		}
		else
			printf("no a_lighting ptr\n");
		printf("\n");
		if (mini->camera)
		{
			printf("camera ptr : %p\n", mini->camera);
			print_xyz(mini->camera->coord, "camera coord");
			print_xyz(mini->camera->vec, "camera vec");
			printf("camera hfov : %f\n", mini->camera->hfov);
			printf("camera vfov : %f\n", mini->camera->vfov);
		}
		else
			printf("no camera ptr\n");
		printf("\n");
		if (tmp_l)
		{
			while (tmp_l)
			{
				printf("light index : %d\n", tmp_l->index);
				printf("light ptr : %p\n", tmp_l);
				print_xyz(mini->light->coord, "light coord");
				printf("light ratio : %f\n", tmp_l->ratio);
				print_colors(mini->light->colors, "light colors");
				printf("light next : %p\n", tmp_l->next);
				tmp_l = tmp_l->next;
				printf("\n");
			}
		}
		else
		{
			printf("no light ptr\n");
			printf("\n");
		}
		if (tmp)
		{
			while (tmp)
			{
				if (tmp->type == SPHERE)
				{
					printf("sphere ptr : %p\n", tmp);
					print_xyz(tmp->info.sphere.coord, "sphere coord");
					printf("sphere diameter : %f\n", tmp->info.sphere.diameter);
					print_colors(tmp->info.sphere.colors, "sphere colors");
					printf("next ptr : %p\n", tmp->next);
				}
				else if (tmp->type == PLANE)
				{
					printf("plane ptr : %p\n", tmp);
					print_xyz(tmp->info.plane.coord, "plane coord");
					print_xyz(tmp->info.plane.vec, "plane vec");
					print_colors(tmp->info.plane.colors, "plane colors");
					printf("next ptr : %p\n", tmp->next);
				}
				else if (tmp->type == CYLINDER)
				{
					printf("cylinder ptr : %p\n", tmp);
					print_xyz(tmp->info.cylinder.coord, "cylinder coord");
					print_xyz(tmp->info.cylinder.vec, "cylinder vec");
					printf("cylinder diameter : %f\n",
						tmp->info.cylinder.diameter);
					printf("cylinder height : %f\n", tmp->info.cylinder.height);
					print_colors(tmp->info.cylinder.colors, "cylinder colors");
					printf("next ptr : %p\n", tmp->next);
				}
				printf("\n");
				tmp = tmp->next;
			}
		}
		else
		{
			printf("no bject ptr\n");
			printf("\n");
		}
		if (mini->fd)
			printf("fd : %d\n", mini->fd);
		else
			printf("no fds available\n");
		printf("\n");
	}
	else
		printf("debug : no mini\n");
	printf("-----debug-----\n");
	return ;
}
