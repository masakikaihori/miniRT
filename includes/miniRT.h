/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:07:48 by mkaihori          #+#    #+#             */
/*   Updated: 2024/12/30 18:18:22 by mkaihori         ###   ########.fr       */
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

typedef enum e_objecttype
{
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	UNKNOWN,
}	t_objecttype;

typedef struct s_object
{
	t_objecttype	type;
	char			*info1;
	char			*info2;
	char			*info3;
	char			*info4;
	char			*info5;
	struct s_object	*next;
}	t_object;

typedef struct s_mini
{
	void				*mlx;
	void				*win;
	struct s_object		*object;
	int					status;
}	t_mini;

//exit.c
void		print_error(char *str);
int			free_exit(t_mini *mini, int status);
void		print_free_exit(t_mini *mini, char *str, int status);

t_object	*read_scene(t_mini *mini, char *file);

#endif