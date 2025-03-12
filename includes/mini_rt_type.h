/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:38:32 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/12 15:08:45 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_TYPE_H
# define MINI_RT_TYPE_H

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

typedef enum e_cyl_inter
{
	CYL_SIDE,
	CYL_UP,
	CYL_DOWN,
}	t_cyl_inter;

typedef struct s_rgb
{
	short	red;
	short	green;
	short	blue;
}	t_rgb;

typedef struct s_xyz
{
	double	x;
	double	y;
	double	z;
}	t_xyz;

typedef struct s_a_lightning
{
	double	ratio;
	t_rgb	colors;
	int		color;
}	t_a_lightning;

typedef struct s_camera
{
	t_xyz	coord;
	t_xyz	vec;
	double	hfov;
	double	vfov;
}	t_camera;

typedef struct s_light
{
	t_xyz	coord;
	double	ratio;
	t_rgb	colors;
	int		color;
}	t_light;

typedef struct s_sphere
{
	int		index;
	t_xyz	coord;
	double	diameter;
	t_rgb	colors;
	int		color;
}	t_sphere;

typedef struct s_plane
{
	int		index;
	t_xyz	coord;
	t_xyz	vec;
	t_rgb	colors;
	int		color;
}	t_plane;

typedef struct s_cylinder
{
	int		index;
	t_xyz	coord;
	t_xyz	vec;
	double	diameter;
	double	height;
	t_rgb	colors;
	int		color;
	t_xyz	upside;
	t_xyz	downside;
}	t_cylinder;

typedef struct s_hit
{
	double		t;
	int			color;
	int			index;
	t_xyz		intersection;
	t_cyl_inter	cylinder;
	double		diff;
	double		spec;
}	t_hit;

typedef union u_oinfo
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_oinfo;

typedef struct s_object
{
	int				index;
	t_otype			type;
	t_oinfo			info;
	struct s_object	*next;
}	t_object;

typedef struct s_mini
{
	void			*mlx;
	void			*win;
	t_a_lightning	*a_lightning;
	t_camera		*camera;
	t_light			*light;
	t_object		*object;
	t_xyz			world_up;
	t_xyz			right_vec;
	t_xyz			up_vec;
	double			distance;
	double			x_pixel;
	double			y_pixel;
	int				status;
	int				fd;
}	t_mini;

#endif