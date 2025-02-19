/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:38:32 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/19 17:21:29 by mkaihori         ###   ########.fr       */
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
	float			hfov;
	float			vfov;
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

#endif