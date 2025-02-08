/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/02 19:21:04 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>

# include "mlx.h"

# include "libft.h"
# include "get_next_line.h"

typedef enum e_otype
{
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	UNKNOWN,
}	t_otype;

typedef	struct s_rgb
{
	short	red;
	short	green;
	short	blue;
}	t_rgb;

typedef	struct s_a_lighting
{
	float			ratio;
	struct s_rbg	color;
}	t_a_lighting;

typedef struct s_camera
{
	struct s_xyz	coordinates;
	struct s_vector	vector;
	short			fov;
}	t_camera;

typedef struct s_light
{
	struct s_xyz	coordinates;
	float			ratio;
	struct s_rbg	color;
}	t_light;

struct union u_oinfo
{
	
}	t_oinfo;

typedef struct s_object
{
	struct e_objecttype	type;
	struct u_oinfo		info;
	struct s_object		*next;
}	t_object;

typedef struct s_obj
{
	struct s_a_lighting	*a_lighting;
	struct s_camera		*camera;
	struct s_light		*light;
	struct s_object		*object;
}	t_obj;

typedef struct s_mini
{
	void				*mlx;
	void				*win;
	struct s_obj		object;
	int					status;
}	t_mini;

//exit.c
void		print_error(char *str);
int			free_mini(t_mini *mini);
int			free_exit(t_mini *mini);
void		print_free_exit(t_mini *mini, char *str, int status);

t_object	*read_scene(t_mini *mini, char *file);

char	**rt_split(t_mini *mini, char *str);

void	free_strs(char **strs);

#endif