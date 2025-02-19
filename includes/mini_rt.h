/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/19 16:38:28 by mkaihori         ###   ########.fr       */
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
//set_utiles
t_xyz			set_xyz(t_mini *mini, char **strs, char *str);
t_rgb			set_rgb(t_mini *mini, char **strs, char *str);
bool			not_available(char **strs);
bool			vec_range(t_xyz vec);
short			rt_atos(t_mini *mini, char **strs, char *str, int *index);
float			rt_atof(t_mini *mini, char **strs, char *str, int *index);
int				rt_strslen(char **strs);
//debug
void			print_mini(t_mini *mini);
void			*debug_malloc(size_t size);
void			debug_free(void *prt);

#endif