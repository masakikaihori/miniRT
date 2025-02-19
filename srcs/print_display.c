/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:44:27 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/19 22:27:25 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	print_display(t_mini *mini)
{
	float	w;
	float	h;
	float	hfov;
	float	vfov;
	int		i;
	t_xyz	tmp;

	w = tan(mini->camera->hfov / 180 * M_PI);
	h = tan(mini->camera->vfov / 180 * M_PI);
	vfov = mini->camera->vfov;
	tmp.x = -w;
	tmp.y = h;
	tmp.z = 1;
	i = 1;
	while (tmp.y > -h)
	{
		hfov = mini->camera->hfov;
		tmp.x = -tan(hfov / 180 * M_PI);
		while (tmp.x < w)
		{
			printf("%d:%f,%f   ", i, tmp.x, tmp.y);
			i++;
			hfov -= mini->camera->hfov/(WIDTH/2.0);
			tmp.x = -tan(hfov / 180 * M_PI);
		}
		vfov -= mini->camera->vfov/(HEIGHT/2.0);
		tmp.y = tan(vfov / 180 * M_PI);
	}
	return ;
}
