/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:36:05 by mkaihori          #+#    #+#             */
/*   Updated: 2025/03/24 15:57:40 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	free_strs(char **strs)
{
	int	index;

	if (strs)
	{
		index = 0;
		while (strs[index])
		{
			free(strs[index]);
			index++;
		}
		free(strs);
	}
	return ;
}

void	free_objects(t_mini *mini)
{
	t_object	*tmp_o;
	t_light		*tmp_l;

	tmp_o = mini->object;
	tmp_l = mini->light;
	while (tmp_o)
	{
		mini->object = mini->object->next;
		free(tmp_o);
		tmp_o = mini->object;
	}
	if (mini->a_lighting)
		free(mini->a_lighting);
	if (mini->camera)
		free(mini->camera);
	while (tmp_l)
	{
		mini->light = mini->light->next;
		free(tmp_l);
		tmp_l = mini->light;
	}
	return ;
}
