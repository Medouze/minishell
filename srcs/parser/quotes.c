/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:40:51 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/27 23:09:02 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_quotes(char c, char *quote_type, char *new_str, int *j)
{
	if (!(*quote_type))
		*quote_type = c;
	else if (*quote_type == c)
		*quote_type = 0;
	else
		new_str[(*j)++] = c;
}

static char	*remove_matching_quotes(const char *str)
{
	int		i;
	int		j;
	char	quote_type;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	quote_type = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i++;
			new_str[j++] = str[i++];
			continue ;
		}
		if (str[i] == '\'' || str[i] == '\"')
			process_quotes(str[i], &quote_type, new_str, &j);
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_quotes_string(char **str)
{
	char	*new_str;

	new_str = remove_matching_quotes(*str);
	if (!new_str)
		return ;
	free(*str);
	*str = new_str;
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
