/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:14:06 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/25 17:05:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser2(t_token **tokens, char **env)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		expand_dollar(&current->str, env);
		if (ft_strchr(current->str, '\"') || ft_strchr(current->str, '\''))
			remove_quotes(&current->str);
		current = current->next;
	}
	print_tokens(*tokens);
	free_tokens(*tokens);
}
