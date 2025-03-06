/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/03 19:18:23 by mkaihori         ###   ########.fr       */
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

# include "./mini_rt_type.h"
# include "./mini_rt_define.h"

# include "../minilibx-linux/mlx.h"

# include "../libft/libft.h"
# include "../libft/get_next_line.h"

//exit
void			print_error(char *str);
int				free_exit(t_mini *mini);
void			print_free_exit(t_mini *mini, char *str, int status);
void			print_frees_exit(t_mini *mini, char *str,
					int status, char **strs);
//free
int				free_mini(t_mini *mini);
void			free_strs(char **strs);
void			free_objects(t_mini *mini);
//read_scene
void			read_scene(t_mini *mini, char *file);
//read_scene_utiles
char			**rt_split(t_mini *mini, char *str);
void			rt_close(t_mini *mini);
//set
void			set_amb(t_mini *mini, char **strs);
void			set_camera(t_mini *mini, char **strs);
void			set_light(t_mini *mini, char **strs);
void			set_sphere(t_mini *mini, char **strs);
void			set_plane(t_mini *mini, char **strs);
void			set_cylinder(t_mini *mini, char **strs);
void			set_screen(t_mini *mini);
//set_utiles
t_xyz			set_xyz(t_mini *mini, char **strs, char *str);
t_rgb			set_rgb(t_mini *mini, char **strs, char *str);
bool			not_available(char **strs);
bool			vec_range(t_xyz vec);
short			rt_atos(t_mini *mini, char **strs, char *str, int *index);
float			rt_atof(t_mini *mini, char **strs, char *str, int *index);
int				rt_strslen(char **strs);
int				int_color(short red, short green, short blue);

void			print_display(t_mini *mini);

//debug
void			print_mini(t_mini *mini);
void			*debug_malloc(size_t size);
void			debug_free(void *prt);

//vec
float			vec_norm(t_xyz a);
void			normalize(t_xyz *a);
float			innner_product(t_xyz a, t_xyz b);
t_xyz			cross_product(t_xyz a, t_xyz b);
t_xyz			set_vec(float x, float y, float z);
t_xyz			vec_multiplied(float scalar, t_xyz vec);
t_xyz			vec_addition(t_xyz a, t_xyz b);
t_xyz			vec_subtraction(t_xyz a, t_xyz b);
t_xyz			get_ray(t_mini *mini, float distance, float display_x, float display_y);

void			ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera);
void			ray_plane(t_xyz ray, t_plane obj, t_hit *hit, t_xyz camera);

#endif