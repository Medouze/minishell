/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:15:26 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/12 17:41:10 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	proceed_in(char *str, t_token **head, t_token **current, int *i)
{
	t_token	*new;

	if (str[*i + 1] && str[*i + 1] == '<')
	{
		new = new_token (HEREDOC, "<<");
		fill_token(head, current, new);
		(*i) += 2;
	}
	else
	{
		new = new_token(REDIRECT_IN, "<");
		fill_token(head, current, new);
		(*i)++;
	}
}

void	proceed_out(char *str, t_token **head, t_token **current, int *i)
{
	t_token	*new;

	if (str[*i + 1] && str[*i + 1] == '>')
	{
		new = new_token (HEREDOC, ">>");
		fill_token(head, current, new);
		(*i) += 2;
	}
	else
	{
		new = new_token(REDIRECT_IN, ">");
		fill_token(head, current, new);
		(*i)++;
	}
}

void	handle_token(char *str, t_token **head, t_token **current, int *i)
{
	t_token	*new;

	if ((str[*i]) == '|')
	{
		new = new_token(PIPE, "|");
		fill_token(head, current, new);
		(*i)++;
	}
	else if ((str[(*i)]) == '<')
		proceed_in(str, head, current, i);
	else if ((str[*i]) == '>')
		proceed_out(str, head, current, i);
}
