/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:59:17 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/20 21:02:27 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(t_type type, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
		print_error("Failed strdup\n");
	new->type = type;
	new->next = NULL;
	return (new);
}

void	fill_token(t_token **head, t_token **current, t_token *new)
{
	if (*head == NULL)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

void	print_tokens(t_token *head) // A supprimer par la suite(test)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("type: %d, value: '%s'\n", current->type, current->str);
		current = current->next;
	}
}

void	proceed_cmd(char *str, t_token **head, t_token **current, int *i)
{
	int		start;
	char	*cmd_str;
	t_token	*new;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '-' || str[*i] == '_' || str[*i] == '=' || str[*i] == '\'' || str[*i] == '\"' || str[*i] == '$'))
		(*i)++;
	cmd_str = ft_substr(str, start, *i - start);
	if (!cmd_str)
	{
		free_tokens(*head);
		print_error("Memory allocation failed\n");
	}
	new = new_token(CMD, cmd_str);
	free(cmd_str);
	fill_token(head, current, new);
}

t_token	*lexer(char *str, t_shell g_env)
{
	t_token	*head;
	t_token	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			handle_token(str, &head, &current, &i);
		// else if (str[i] == '\"' || str[i] == '\'')
		// 	handle_quotes(str, &i, &current, &head);
		else
			proceed_cmd(str, &head, &current, &i);
	}
	expander(&head, g_env);
	print_tokens(head);
	return (head);
}
