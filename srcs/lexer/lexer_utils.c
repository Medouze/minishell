/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:15:26 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/28 01:26:04 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	handle_in_out(char *str, t_token **head, t_token **current, int *i)
{
	t_token	*new;

	new = NULL;
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

int	check_closed(char *str)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!current_quote)
				current_quote = str[i];
			else if (str[i] == current_quote)
				current_quote = 0;
		}
		i++;
	}
	return (current_quote == 0);
}

int	handle_quotes(char *str, int *i, t_token **current, t_token **head)
{
	int		start;
	char	*content;
	t_token	*new;
	char	quote_type;

	quote_type = str[*i];
	start = (*i);
	(*i)++;
	if (!check_closed(str))
	{
		free_tokens(head);
		printf("syntax error unclosed quotes\n");
		return (0);
	}
	move_to_closing_quote(str, i, quote_type);
	content = ft_substr(str, start, (*i) - start);
	new = new_token(CMD, content);
	free(content);
	fill_token(head, current, new);
	if (str[*i])
		(*i)++;
	return (1);
}
