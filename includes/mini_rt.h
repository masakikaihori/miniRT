/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/17 18:17:47 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"

# include "../libft/libft.h"
# include "../libft/get_next_line.h"

# define AMB_ELE 3
# define CAM_ELE 4
# define LIG_ELE 4
# define SPH_ELE 4
# define PLA_ELE 4
# define CYL_ELE 6
# define ATOS_MAX 255
# define FOV_MAX 180

# define OK_CHARSET "0123456789+-.,eE"

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

typedef struct s_rgb
{
	short	red;
	short	green;
	short	blue;
}	t_rgb;

typedef struct s_xyz
{
	float	x;
	float	y;
	float	z;
}	t_xyz;

typedef struct s_a_lightning
{
	float			ratio;
	struct s_rgb	color;
}	t_a_lightning;

typedef struct s_camera
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	short			fov;
}	t_camera;

typedef struct s_light
{
	struct s_xyz	coord;
	float			ratio;
	struct s_rgb	color;
}	t_light;

typedef struct s_sphere
{
	struct s_xyz	coord;
	float			diameter;
	struct s_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	struct s_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	float			diameter;
	float			height;
	struct s_rgb	color;
}	t_cylinder;

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

typedef struct s_mini
{
	void					*mlx;
	void					*win;
	struct s_a_lightning	*a_lightning;
	struct s_camera			*camera;
	struct s_light			*light;
	struct s_object			*object;
	int						status;
	int						fd;
}	t_mini;

//exit.c
void			print_error(char *str);
int				free_mini(t_mini *mini);
int				free_exit(t_mini *mini);
void			print_free_exit(t_mini *mini, char *str, int status);
void			print_frees_exit(t_mini *mini, char *str, int status, char **strs);

void			read_scene(t_mini *mini, char *file);

void			set_amb(t_mini *mini, char **strs);
void			set_camera(t_mini *mini, char **strs);
void			set_light(t_mini *mini, char **strs);
void			set_sphere(t_mini *mini, char **strs);
void			set_plane(t_mini *mini, char **strs);
void			set_cylinder(t_mini *mini, char **strs);

t_xyz			set_xyz(t_mini *mini, char **strs, char *str);
t_rgb			set_rgb(t_mini *mini, char **strs, char *str);
bool			not_available(char **strs);
bool			vec_range(t_xyz vec);

char			**rt_split(t_mini *mini, char *str);
int				rt_strslen(char **strs);
short			rt_atos(t_mini *mini, char **strs, char *str, int *index);
float			rt_atof(t_mini *mini, char **strs, char *str, int *index);
void			rt_close(t_mini *mini);

void			free_strs(char **strs);
void    		free_objects(t_mini *mini);

//debug
void    		print_mini(t_mini *mini);
void			*debug_malloc(size_t size);
void			debug_free(void *prt);

#endif