/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:15:26 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/20 21:28:26 by mlavergn         ###   ########.fr       */
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

void	handle_in_out(char *str, t_token **head, t_token **current, int *i)
{
	t_token	*new;

	if ((str[*i + 1] && str[*i + 1] == '<')
		|| (str[*i + 1] && str[*i + 1] == '>'))
	{
		if (str[*i + 1] == '<')
			new = new_token (HEREDOC, "<<");
		else if (str[*i + 1] == '>')
			new = new_token (APPEND, ">>");
		fill_token(head, current, new);
		(*i) += 2;
	}
	else
	{
		if (str[*i] == '<')
			new = new_token(REDIRECT_IN, "<");
		else if (str[*i] == '>')
			new = new_token(REDIRECT_OUT, ">");
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
	else if (str[*i] == '<' || str[*i] == '>')
		handle_in_out(str, head, current, i);
}

int	check_closed(char *str, char quote)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == quote)
			in_quote = !in_quote;
		i++;
	}
	return (in_quote == 0);
}

void	handle_quotes(char *str, int *i, t_token **current, t_token **head)
{
	int		start;
	char	*content;
	t_token	*new;
	char	quote_type;

	quote_type = str[*i];
	if (!check_closed(str, quote_type))
	{
		free_tokens(*head);
		print_error("Unclosed quotes\n");
	}
	if (quote_type == '\"')
		expand_dollar(str);
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != quote_type)
		(*i)++;
	content = ft_substr(str, start, *i - start);
	new = new_token(CMD, content);
	free(content);
	fill_token(head, current, new);
	(*i)++;
}
