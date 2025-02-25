/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:14:06 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/25 16:44:54 by mlavergn         ###   ########.fr       */
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
		if (current->str[0] == '\"' || current->str[0] == '\'')
			remove_quotes(&current->str);

		current = current->next;
	}
	print_tokens(*tokens);
	free_tokens(*tokens);
}
