/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_define.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <mkaihori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:38:34 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 17:32:07 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_DEFINE_H
# define MINI_RT_DEFINE_H

# define WIDTH 640.0
# define HEIGHT 480.0
# define DIF_REF 0.7
# define SPE_REF 0.8
# define SHINE 5.0
# define NEAR_ZERO 1e-6

# define A 0
# define B 1
# define C 2
# define D 3

# define P_LIGHT 0
# define V_NORMAL 1
# define V_LIGHT 2
# define V_REFLIGHT 3

# define AMB_ELE 3
# define CAM_ELE 4
# define LIG_ELE 4
# define SPH_ELE 4
# define PLA_ELE 4
# define CYL_ELE 6

# define ATOS_MAX 255
# define HFOV_MAX 180
# define LIGHT_MAX 8
# define LIGHT_BITS 128

# define ESC_KEY 65307

# define OK_CHARSET "0123456789+-.,eE"

#endif