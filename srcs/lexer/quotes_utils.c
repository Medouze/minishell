/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:40:51 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/26 16:28:52 by mlavergn         ###   ########.fr       */
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

	count = 0;
	quote_nbr = get_nbr_quotes(str, quote_type);
	while (str[*i] && count < quote_nbr)
	{
		if (str[*i] == quote_type)
			count++;
		(*i)++;
	}
}
