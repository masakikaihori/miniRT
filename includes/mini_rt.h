/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 17:01:03 by mkaihori         ###   ########.fr       */
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

# include "../libft/includes/libft.h"

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
t_xyz			set_xyz(t_mini *mini, char **strs, char *str, int sign);
t_rgb			set_rgb(t_mini *mini, char **strs, char *str);
bool			not_available(char **strs);
bool			vec_range(t_xyz vec);
short			rt_atos(t_mini *mini, char **strs, char *str, int *index);
double			rt_atof(t_mini *mini, char **strs, char *str, int *index);
int				rt_strslen(char **strs);
int				light_count(t_mini *mini);
//vec
double			vec_norm(t_xyz a);
void			normalize(t_xyz *a);
double			inner_pro(t_xyz a, t_xyz b);
t_xyz			cross_pro(t_xyz a, t_xyz b);
t_xyz			set_vec(double x, double y, double z);
t_xyz			vec_mul(double scalar, t_xyz vec);
t_xyz			vec_add(t_xyz a, t_xyz b);
t_xyz			vec_sub(t_xyz a, t_xyz b);
t_xyz			get_ray(t_mini *mini, double distance,
					double display_x, double display_y);
//display
void			print_display(t_mini *mini);
void			ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera);
void			ray_plane(t_xyz ray, t_plane obj, t_hit *hit, t_xyz camera);
void			ray_cyl_side(t_xyz ray, t_cylinder obj,
					t_hit *hit, t_xyz camera);
void			ray_cyl_surface(t_xyz ray, t_cylinder obj,
					t_hit *hit, t_xyz camera);

bool			in_height(double t, double h[2]);
void			set_hit(t_hit *hit, t_rgb colors, double t, int index);
void			set_hit_cylinder(t_hit *hit, double t,
					t_cylinder obj, t_cyl_inter p);
bool			in_upcircle(t_xyz ray, t_cylinder obj, t_xyz camera, double t);
bool			in_downcircle(t_xyz ray, t_cylinder obj,
					t_xyz camera, double t);
void			cal_height(t_cylinder obj, t_xyz camera,
					t_xyz ray, double h[2]);

int				not_shadow(t_object *objs, t_light *light, t_xyz point, t_hit *hit);
int				shadow_sphere(t_xyz ray, t_sphere obj, t_xyz point, double max);
int				shadow_plane(t_xyz ray, t_plane obj, t_xyz point, double max);
int				shadow_cyl_side(t_xyz ray, t_cylinder obj, t_xyz point, double max);
int				shadow_cyl_surface(t_xyz ray, t_cylinder obj, t_xyz point, double max);

void			sphere_light(t_xyz ray, t_light *light, t_hit *hit, t_sphere obj);
void			plane_light(t_xyz ray, t_light *light, t_hit *hit, t_plane obj);
void			cylinder_light(t_xyz ray, t_light *light,
					t_hit *hit, t_cylinder obj);

t_xyz			cylinder_normal_vec(t_hit *hit, t_cylinder obj);
t_xyz			reflection_vec(t_xyz normal_vec, t_xyz light_vec);
double			spec_light(double ratio, t_xyz reflight_vec, t_xyz ray);

void			cal_color(t_hit *hit, t_rgb t, t_a_lighting *amb_light);
int				int_color(short red, short green, short blue);

//debug
void			print_mini(t_mini *mini);
void			*debug_malloc(size_t size);
void			debug_free(void *prt);

#endif