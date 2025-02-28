/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:14:06 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/28 01:27:33 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe_errors(t_token *current)
{
	if (current->type == PIPE)
	{
		if (!current->next)
		{
			printf("syntax error: no command after pipe\n");
			return (1);
		}
		if (current->next->type == PIPE)
		{
			printf("syntax error near unexpected token '|'\n");
			return (1);
		}
	}
	return (0);
}

int	check_redir_errors(t_token *current)
{
	if (current->type >= REDIRECT_IN && current->type <= HEREDOC)
	{
		if (!current->next)
		{
			printf("syntax error near unexpected token 'newline'\n");
			return (1);
		}
		else
		{
			printf("syntax error near unexpected token '%s'\n",
				current->next->str);
			return (1);
		}
	}
	return (0);
}

int	check_errors(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == PIPE)
	{
		printf("syntax error near unexpected token '|'\n");
		return (1);
	}
	while (current)
	{
		if (check_pipe_errors(current))
			return (1);
		if (check_redir_errors(current))
			return (1);
		current = current->next;
	}
	return (0);
}

void	parser2(t_token **tokens, t_shell *g_env)
{
	t_token	*current;

	if (!(*tokens))
		return ;
	print_tokens(*tokens);
	current = *tokens;
	while (current)
	{
		expand_dollar(&current->str, (*g_env));
		if (ft_strchr(current->str, '\"') || ft_strchr(current->str, '\''))
			remove_quotes(&current->str);
		if (check_errors(*tokens))
		{
			g_env->last_exit = 2;
			break ;
		}
		current = current->next;
	}
	print_tokens(*tokens);
	free_tokens(tokens);
}
