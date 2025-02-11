/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaihori <nana7hachi89gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:08:15 by mkaihori          #+#    #+#             */
/*   Updated: 2025/02/11 16:40:33 by mkaihori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/mini_rt.h"

int	count_words(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index] && str[index] != '\n')
	{
		while (str[index] == ' ' || str[index] == '\t')
			index++;
		if (str[index] != '\n' && str[index])
			count++;
		while (str[index] && str[index] != '\n'
			&& str[index] != ' ' && str[index] != '\t')
			index++;
	}
	return (count);
}

char	*get_str(char *str, int index)
{
	char	*splited;
	int		size;

	size = 0;
	while (str[index + size] != '\n' && str[index + size]
		&& str[index + size] != ' ' && str[index + size] != '\t')
		size++;
	splited = (char *)malloc(sizeof(char) * (size + 1));
	if (!splited)
		return (NULL);
	splited[size--] = '\0';
	while (size >= 0)
	{
		splited[size] = str[index + size];
		size--;
	}
	return (splited);
}

void	split_error(t_mini *mini, char **strs, char *str, int word)
{
	while (--word >= 0)
		free(strs[word]);
	free(strs);
	free(str);
	print_free_exit(mini, NULL, errno);
	return ;
}

void	splited(t_mini *mini, char **strs, char *str)
{
	int	index;
	int	word;

	index = 0;
	word = 0;
	while (str[index] && str[index] != '\n')
	{
		while (str[index] == ' ' || str[index] == '\t')
			index++;
		if (str[index] != '\n' && str[index])
		{
			strs[word] = get_str(str, index);
			if (!strs[word])
				split_error(mini, strs, str, word);
			word++;
		}
		while (str[index] && str[index] != '\n'
			&& str[index] != ' ' && str[index] != '\t')
			index++;
	}
	return ;
}

char	**rt_split(t_mini *mini, char *str)
{
	char	**strs;
	int		word_count;

	word_count = count_words(str);
	if (!word_count)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!strs)
	{
		free(str);
		print_free_exit(mini, NULL, errno);
	}
	strs[word_count] = NULL;
	splited(mini, strs, str);
	return (strs);
}
