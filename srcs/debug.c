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

void    print_xyz(t_xyz xyz, char *str)
{
	printf("%s x : %f\n", str, xyz.x);
	printf("%s y : %f\n", str, xyz.y);
	printf("%s z : %f\n", str, xyz.z);
	return ;
}

void    print_color(t_rgb color, char *str)
{
	printf("%s red : %d\n", str, color.red);
	printf("%s green : %d\n", str, color.green);
	printf("%s blue : %d\n", str, color.blue);
}

void    print_mini(t_mini *mini)
{
	t_object    *tmp;

	tmp = mini->object;
	if (mini)
	{
		if (mini->mlx)
			printf("mlx ptr : %p\n", mini->mlx);
		else
			printf("no mlx ptr\n");
		if (mini->win)
			printf("win ptr : %p\n", mini->win);
		else
			printf("no win ptr\n");
		if (mini->a_lightning)
		{
			printf("a_lightning ptr : %p\n", mini->a_lightning);
			printf("a_lightning ratio : %f\n", mini->a_lightning->ratio);
			print_color(mini->a_lightning->color, "a_lightning color");
		}
		else
			printf("no a_lightning ptr\n");
		if (mini->camera)
		{
			printf("camera ptr : %p\n", mini->camera);
			print_xyz(mini->camera->coord, "camera coord");
			print_xyz(mini->camera->vec, "camera vec");
			printf("camera fov : %d\n", mini->camera->fov);
		}
		else
			printf("no camera ptr\n");
		if (mini->light)
		{
			printf("light ptr : %p\n", mini->light);
			print_xyz(mini->light->coord, "light coord");
			printf("light ratio : %f\n", mini->light->ratio);
			print_color(mini->light->color, "light color");
		}
		else
			printf("no light ptr\n");
		if (tmp)
		{
			if (tmp->type == SPHERE)
			{
				printf("sphere ptr : %p\n", tmp);
				print_xyz(tmp->info.sphere.coord, "sphere coord");
				printf("sphere diameter : %f\n", tmp->info.sphere.diameter);
				print_color(tmp->info.sphere.color, "sphere color");
			}
			else if (tmp->type == PLANE)
			{
				printf("plane ptr : %p\n", tmp);
				print_xyz(tmp->info.plane.coord, "plane coord");
				print_xyz(tmp->info.plane.vec, "plane vec");
				print_color(tmp->info.plane.color, "palne color");
			}
			else if (tmp->type == CYLINDER)
			{
				printf("cylinder ptr : %p\n", tmp);
				print_xyz(tmp->info.cylinder.coord, "cylinder coord");
				print_xyz(tmp->info.cylinder.vec, "cylinder vec");
				printf("cylinder diameter : %f\n", tmp->info.cylinder.diameter);
				printf("cylinder height : %f\n", tmp->info.cylinder.height);
				print_color(tmp->info.cylinder.color, "cylinder color");
			}
			tmp = tmp->next;
		}
		else
			printf("no bject ptr\n");
		if (mini->fd)
			printf("fd : %d\n", mini->fd);
		else
			printf("no fds available\n");
	}
	else
		printf("debug : no mini\n");
	return ;
}
