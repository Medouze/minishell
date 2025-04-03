/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:12:02 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/02 21:04:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

t_simple_cmds	*allocate_new_command(int len)
{
	t_simple_cmds	*new_cmd;

	new_cmd = malloc(sizeof(t_simple_cmds));
	if (!new_cmd)
	{
		perror("Memory allocation failed for new_cmd");
		return (NULL);
	}
	ft_memset(new_cmd, 0, sizeof(t_simple_cmds));
	new_cmd->args = malloc(sizeof(char *) * (len + 1));
	if (!new_cmd->args)
	{
		perror("Memory allocation failed for args");
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

void	add_command_to_list(t_simple_cmds **exec_token,
	t_simple_cmds *current_cmd, t_simple_cmds **last_cmd)
{
	if (!*exec_token)
		*exec_token = current_cmd;
	else
		(*last_cmd)->next = current_cmd;
	*last_cmd = current_cmd;
}

void	handle_redir(t_simple_cmds *exec_cmd, t_token **tokens)
{
	if ((*tokens)->type == REDIRECT_IN)
	{
		exec_cmd->infile = (*tokens)->next->str;
		*tokens = (*tokens)->next->next;
	}
	else if ((*tokens)->type == REDIRECT_OUT)
	{
		add_outfile(&exec_cmd->outfiles, (*tokens)->next->str, 0);
		*tokens = (*tokens)->next->next;
	}
	else if ((*tokens)->type == APPEND)
	{
		add_outfile(&exec_cmd->outfiles, (*tokens)->next->str, 1);
		*tokens = (*tokens)->next->next;
	}
	else if ((*tokens)->type == HEREDOC)
	{
		add_heredoc(&exec_cmd->heredocs, (*tokens)->next->str);
		*tokens = (*tokens)->next->next;
	}
}

int	fill_args(t_simple_cmds *cmd, t_token **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*tokens) && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == CMD)
		{
			cmd->args[i] = ft_strdup((*tokens)->str);
			i++;
		}
		if ((*tokens) && ((*tokens)->type >= REDIRECT_IN
				&& (*tokens)->type <= HEREDOC))
			handle_redir(cmd, tokens);
		else if ((*tokens)->type == PIPE)
			break ;
		else
			(*tokens) = (*tokens)->next;
	}
	cmd->args[i] = NULL;
	return (0);
}

t_simple_cmds	*tokenize(t_token *tokens)
{
	t_simple_cmds	*exec_token;
	t_simple_cmds	*current_cmd;
	t_simple_cmds	*last_cmd;

	exec_token = NULL;
	while (tokens)
	{
		current_cmd = allocate_new_command(get_nbr_cmd(tokens));
		if (!current_cmd)
			return (NULL);
		if (fill_args(current_cmd, &tokens) == -1)
		{
			free(current_cmd);
			return (NULL);
		}
		add_command_to_list(&exec_token, current_cmd, &last_cmd);
		if (!tokens)
			break ;
		else if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
		else
			tokens = tokens->next;
	}
	return (exec_token);
}
