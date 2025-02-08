/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:52:09 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/02 17:54:09 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

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
