/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/08 17:38:37 by mkaihori         ###   ########.fr       */
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

#define AMB_ELE 3
#define CAM_ELE 4
#define LIG_ELE 4
#define SPH_ELE 4
#define PLA_ELE 4
#define CYL_ELE 6
#define COLOR_MAX 255

typedef enum e_otype
{
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	UNKNOWN,
}t_otype;

typedef struct s_rgb
{
	short	red;
	short	green;
	short	blue;
}t_rgb;

typedef struct s_xyz
{
	float	x;
	float	y;
	float	z;
}t_xyz;

typedef	struct s_a_lighting
{
	float			ratio;
	struct s_rgb	color;
}t_a_lighting;

typedef struct s_camera
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	short			fov;
}t_camera;

typedef struct s_light
{
	struct s_xyz	coordinates;
	float			ratio;
	struct s_rgb	color;
}	t_light;

typedef struct s_sphere
{
	struct s_xyz	coord;
	float			diameter;
	struct s_rgb	color;
}t_sphere;

typedef struct s_plane
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	struct s_rgb	color;
}t_plane;

typedef struct s_cylinder
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	float			diameter;
	float			height;
	struct s_rgb	color;
}t_cylinder;


typedef union u_oinfo
{
	struct s_sphere		sphere;
	struct s_plane		plane;
	struct s_cylinder	cylinder;
}	t_oinfo;

typedef struct s_object
{
	enum e_otype		type;
	union u_oinfo		info;
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
void			print_error(char *str);
int				free_mini(t_mini *mini);
int				free_exit(t_mini *mini);
void			print_free_exit(t_mini *mini, char *str, int status);

void			read_scene(t_mini *mini, char *file);
t_a_lighting	*set_amb(t_mini *mini, char **strs);
char			**rt_split(t_mini *mini, char *str);
int				rt_strslen(char **strs);
short			rt_atos(t_mini *mini, char **strs, char *str, int *index);

void			free_strs(char **strs);

#endif