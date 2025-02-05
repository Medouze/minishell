/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:59:17 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/05 15:36:51 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*lexer(char **line)
{
	int		i;
	int		tok_len;
	t_token	*tokens;

	i = 1;
	tok_len = 0;
	while (line[tok_len])
		tok_len++;
	tokens = malloc(sizeof(t_token) * tok_len);
	tokens[0].type = CMD;
	tokens[0].str = ft_strdup(line[0]);
	while (line[i])
	{
		tokens[i].str = ft_strdup(line[i]);
		if (strncmp(line[i])
	}
}