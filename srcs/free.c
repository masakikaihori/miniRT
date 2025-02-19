/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:36:05 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/19 16:36:05 by mkaihori         ###   ########.fr       */
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
	t_object	*tmp;

	tmp = mini->object;
	while (tmp)
	{
		mini->object = mini->object->next;
		free(tmp);
		tmp = mini->object;
	}
	if (mini->a_lightning)
		free(mini->a_lightning);
	if (mini->camera)
		free(mini->camera);
	if (mini->light)
		free(mini->light);
	return ;
}
