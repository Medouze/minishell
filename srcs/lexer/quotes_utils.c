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

int	get_nbr_quotes(char *str, char quote_type)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
			count++;
		i++;
	}
	return (count);
}

void	move_to_closing_quote(char *str, int *i, char quote_type)
{
	int	quote_nbr;
	int	count;

	count = 1;
	quote_nbr = get_nbr_quotes(str, quote_type);
	while (str[*i] && count < quote_nbr)
	{
		if (str[*i] == quote_type)
			count++;
		(*i)++;
	}
}

void	copy_quoted_content(char *buffer, int *buf_index, char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	buffer[(*buf_index)++] = quote;
	while (str[*i] && str[*i] != quote)
		buffer[(*buf_index)++] = str[(*i)++];
	if (str[*i] == quote)
	{
		buffer[(*buf_index)++] = str[*i];
		(*i)++;
	}
}
