/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:51:56 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/25 15:25:09 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes_string(char **str)
{
	int		i;
	char	*first_word;
	char	*second_word;
	
	i = 1;
	if ((*str)[0] == '\"')
	{
		while ((*str)[i] != '\"')
			i++;
	}
	else
	{
		while ((*str)[i] != '\'')
			i++;
	}
	first_word = ft_substr(*str, 1, i - 1);
	second_word = ft_substr(*str, i + 1, ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(first_word, second_word);
	free(first_word);
	free(second_word);
}

void	remove_quotes(char **str)
{
	char	*temp;

	if (((*str)[0] == '\"' && (*str)[ft_strlen(*str) - 1] == '\"')
		|| ((*str)[0] == '\'' && (*str)[ft_strlen(*str) - 1] == '\''))
	{
		temp = ft_substr(*str, 1, ft_strlen(*str) - 2);
		free(*str);
		*str = ft_strdup(temp);
		free(temp);
	}
	else
		remove_quotes_string(str);
}
