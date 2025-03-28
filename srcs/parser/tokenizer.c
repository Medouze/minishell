/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:12:02 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/28 23:04:06 by mlavergn         ###   ########.fr       */
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

int	fill_args(t_simple_cmds *cmd, t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens && (tokens->type == CMD))
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

#include <stdio.h>

void print_outfiles(t_outfile *outfiles)
{
    while (outfiles)
    {
        printf("Output file: %s, Append: %d\n", outfiles->filename, outfiles->append);
        outfiles = outfiles->next;
    }
}

void print_heredocs(t_heredoc *heredocs)
{
    while (heredocs)
    {
        printf("Heredoc delimiter: %s\n", heredocs->delimiter);
        heredocs = heredocs->next;
    }
}

void print_simple_cmd(t_simple_cmds *cmd)
{
    while (cmd)
    {
        // Print args
        printf("Arguments: ");
        for (int i = 0; cmd->args && cmd->args[i]; i++)
        {
            printf("%s ", cmd->args[i]);
        }
        printf("\n");

        // Print input file
        if (cmd->infile)
        {
            printf("Input file: %s\n", cmd->infile);
        }

        // Print heredocs
        if (cmd->heredocs)
        {
            print_heredocs(cmd->heredocs);
        }

        // Print output files
        if (cmd->outfiles)
        {
            print_outfiles(cmd->outfiles);
        }

        // Move to the next command in the list
        cmd = cmd->next;
    }
}


t_simple_cmds	*tokenize(t_token *tokens)
{
	t_simple_cmds	*exec_token;
	t_simple_cmds	*current_cmd;
	t_simple_cmds	*last_cmd;
	t_token			*current;

	exec_token = NULL;
	while (tokens)
	{
		current = tokens;
		current_cmd = allocate_new_command(get_nbr_cmd(&tokens));
		if (!current_cmd)
			return (NULL);
		if (fill_args(current_cmd, current) == -1)
		{
			free(current_cmd);
			return (NULL);
		}
		add_command_to_list(&exec_token, current_cmd, &last_cmd);
		while (tokens && (tokens->type >= REDIRECT_IN
				&& tokens->type <= HEREDOC))
			handle_redir(current_cmd, &tokens);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	print_simple_cmd(exec_token);
	return (exec_token);
}
