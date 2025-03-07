/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:12:02 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/07 17:03:40 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	fill_args(t_simple_cmds *cmd, t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens && tokens->type == CMD)
	{
		cmd->args[i] = ft_strdup(tokens->str);
		if (!cmd->args[i])
		{
			while (j < i)
			{
				free(cmd->args[j]);
				j++;
			}
			free(cmd->args);
			return (-1);
		}
		i++;
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	return (0);
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

void	handle_redir(t_simple_cmds **exec_token, t_token **tokens)
{
	if ((*tokens)->type == REDIRECT_IN)
		(*exec_token)->infile = (*tokens)->next->str;
	if ((*tokens)->type == REDIRECT_OUT)
		(*exec_token)->outfile = (*tokens)->next->str;
	if ((*tokens)->type == APPEND)
	{
		(*exec_token)->outfile = (*tokens)->next->str;
		(*exec_token)->append = 1;
	}
	if ((*tokens)->type == HEREDOC)
		(*exec_token)->heredoc = (*tokens)->next->str;
	*tokens = (*tokens)->next->next;
}

// Main function to tokenize the input
t_simple_cmds	*tokenize(t_token *tokens)
{
	t_simple_cmds	*exec_token;
	t_simple_cmds	*current_cmd;
	t_simple_cmds	*last_cmd;
	t_token			*current;

	exec_token = NULL;
	current_cmd = NULL;
	last_cmd = NULL;
	while (tokens)
	{
		current = tokens;
		current_cmd = allocate_new_command(get_nbr_cmd(&tokens));
		if (!current_cmd)
			return (NULL);
		fill_args(current_cmd, current);
		add_command_to_list(&exec_token, current_cmd, &last_cmd);
		if (tokens && (tokens->type >= REDIRECT_IN && tokens->type <= HEREDOC))
			handle_redir(&current_cmd, &tokens);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	print_simple_cmds(exec_token);
	return (exec_token);
}
