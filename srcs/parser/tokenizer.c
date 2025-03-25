/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:12:02 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/25 13:49:43 by mlavergn         ###   ########.fr       */
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

void	add_command_to_list(t_simple_cmds **exec_token,
	t_simple_cmds *current_cmd, t_simple_cmds **last_cmd)
{
	if (!*exec_token)
		*exec_token = current_cmd;
	else
		(*last_cmd)->next = current_cmd;
	*last_cmd = current_cmd;
}

void handle_redir(t_simple_cmds **exec_token, t_token **tokens)
{
    // Handle redirection cases (input, output, append, heredoc)
    if ((*tokens)->type == REDIRECT_IN)
    {
        (*exec_token)->infile = (*tokens)->next->str;
        *tokens = (*tokens)->next->next;  // Skip the redirection token and the file name token
    }
    else if ((*tokens)->type == REDIRECT_OUT)
    {
        (*exec_token)->outfile = (*tokens)->next->str;
        *tokens = (*tokens)->next->next;  // Skip the redirection token and the file name token
    }
    else if ((*tokens)->type == APPEND)
    {
        (*exec_token)->outfile = (*tokens)->next->str;
        (*exec_token)->append = 1;
        *tokens = (*tokens)->next->next;  // Skip the append token and the file name token
    }
    else if ((*tokens)->type == HEREDOC)
    {
        (*exec_token)->heredoc = (*tokens)->next->str;
        *tokens = (*tokens)->next->next;  // Skip the heredoc token and the delimiter token
    }
}

// Updated fill_args function to stop when encountering redirection or pipe tokens
int fill_args(t_simple_cmds *cmd, t_token *tokens)
{
    int i = 0;

    // Collect arguments until a redirection or pipe token is encountered
    while (tokens && (tokens->type == CMD))
    {
        cmd->args[i] = ft_strdup(tokens->str);
        if (!cmd->args[i])
        {
            // If memory allocation fails, free all previously allocated args
            for (int j = 0; j < i; j++)
                free(cmd->args[j]);
            free(cmd->args);
            return -1;
        }
        i++;
        tokens = tokens->next;
    }
    cmd->args[i] = NULL;  // Null-terminate the args array
    return 0;
}

// Updated tokenize function to treat redirection as part of a single command
t_simple_cmds *tokenize(t_token *tokens)
{
    t_simple_cmds *exec_token = NULL;
    t_simple_cmds *current_cmd = NULL;
    t_simple_cmds *last_cmd = NULL;
    t_token *current = NULL;

    while (tokens)
    {
        current = tokens;
        current_cmd = allocate_new_command(get_nbr_cmd(&tokens));
        if (!current_cmd)
            return NULL;
        if (fill_args(current_cmd, current) == -1)
        {
            free(current_cmd);
            return NULL;
        }
		add_command_to_list(&exec_token, current_cmd, &last_cmd);
		while (tokens && (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT || tokens->type == APPEND || tokens->type == HEREDOC))
        {
            handle_redir(&current_cmd, &tokens);
        }
        if (tokens && tokens->type == PIPE)
        {
			printf("next\n\n\n");
            tokens = tokens->next;
        }
    }
    return exec_token;
}
