/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:51:56 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/29 00:19:50 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_char(char **str, char *new_str, int *in_single, int *in_double)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !(*in_double))
		{
			*in_single = !(*in_single);
			i++;
			continue ;
		}
		else if ((*str)[i] == '\"' && !(*in_single))
		{
			*in_double = !(*in_double);
			i++;
			continue ;
		}
		new_str[j++] = (*str)[i++];
	}
	new_str[j] = '\0';
}

void	remove_quotes(char **str)
{
	char	*new_str;
	int		in_single;
	int		in_double;

	in_single = 0;
	in_double = 0;
	new_str = (char *)malloc(strlen(*str) + 1);
	if (!new_str)
	{
		printf("Memory allocation failed\n");
		return ;
	}
	process_char(str, new_str, &in_single, &in_double);
	free(*str);
	*str = new_str;
}
