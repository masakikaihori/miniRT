/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:38:32 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/08 19:55:40 by mkaihori         ###   ########.fr       */
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

typedef struct s_hit
{
	double			t;
	struct s_rgb	colors;
	int				color;
}	t_hit;

typedef struct s_a_lightning
{
	double			ratio;
	struct s_rgb	colors;
	int				color;
}	t_a_lightning;

typedef struct s_camera
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	double			hfov;
	double			vfov;
}	t_camera;

typedef struct s_light
{
	struct s_xyz	coord;
	double			ratio;
	struct s_rgb	colors;
	int				color;
}	t_light;

typedef struct s_sphere
{
	struct s_xyz	coord;
	double			diameter;
	struct s_rgb	colors;
	int				color;
}	t_sphere;

typedef struct s_plane
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	struct s_rgb	colors;
	int				color;
}	t_plane;

typedef struct s_cylinder
{
	struct s_xyz	coord;
	struct s_xyz	vec;
	double			diameter;
	double			height;
	struct s_rgb	colors;
	int				color;
	t_xyz			upside;
	t_xyz			downside;
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
	struct s_xyz			world_up;
	struct s_xyz			right_vec;
	struct s_xyz			up_vec;
	double					distance;
	double					x_pixel;
	double					y_pixel;
	int						status;
	int						fd;
}	t_mini;

#endif