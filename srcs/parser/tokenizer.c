/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:12:02 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/01 18:48:41 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_simple_cmds(t_simple_cmds *cmd)
{
    t_simple_cmds *tmp;

    while (cmd)
    {
        if (cmd->args)
        {
            for (int i = 0; cmd->args[i] != NULL; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        tmp = cmd;
        cmd = cmd->next;
        free(tmp);
    }
}


void print_simple_cmds(t_simple_cmds *cmd) // DELETE PLUS TARD
{
    while (cmd)
    {
        printf("Command: ");
        if (cmd->args)
        {
            for (int i = 0; cmd->args[i] != NULL; i++)
                printf("%s ", cmd->args[i]);
        }
        printf("\n");
        if (cmd->infile)
            printf("Input Redirection: %s\n", cmd->infile);
        if (cmd->heredoc)
            printf("Heredoc: %s\n", cmd->heredoc);
        if (cmd->outfile)
        {
            printf("Output Redirection: %s", cmd->outfile);
            if (cmd->append)
                printf(" (append)");
            printf("\n");
        }
        cmd = cmd->next;
    }
}

t_simple_cmds *allocate_new_command(int len)
{
    t_simple_cmds *new_cmd = malloc(sizeof(t_simple_cmds));
    if (!new_cmd)
    {
        perror("Memory allocation failed for new_cmd");
        return NULL;
    }
    memset(new_cmd, 0, sizeof(t_simple_cmds));
    new_cmd->args = malloc(sizeof(char *) * (len + 1));
    if (!new_cmd->args)
    {
        perror("Memory allocation failed for args");
        free(new_cmd);
        return NULL;
    }

    return new_cmd;
}

int fill_args(t_simple_cmds *cmd, t_token *tokens)
{
    int i = 0;

    while (tokens && tokens->type == CMD)
    {
        cmd->args[i] = ft_strdup(tokens->str);
        if (!cmd->args[i])
        {
            for (int j = 0; j < i; j++)
                free(cmd->args[j]);
            free(cmd->args);
            return -1;
        }
        i++;
        tokens = tokens->next;
    }
    cmd->args[i] = NULL;

    return 0;
}

void add_command_to_list(t_simple_cmds **exec_token, t_simple_cmds *current_cmd, t_simple_cmds **last_cmd)
{
    if (!*exec_token)
        *exec_token = current_cmd;
    else
        (*last_cmd)->next = current_cmd;
    *last_cmd = current_cmd;
}

int	get_nbr_cmd(t_token **tokens)
{
	int	len;

	len = 0;
	while (*tokens && (*tokens)->type == CMD) 
	{
		len++;
		*tokens = (*tokens)->next;
	}
	return (len);
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
t_simple_cmds *tokenize(t_token *tokens)
{
    t_simple_cmds *exec_token = NULL;
    t_simple_cmds *current_cmd = NULL;
    t_simple_cmds *last_cmd = NULL;
	t_token			*current;

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
        if (tokens && (tokens->type >= REDIRECT_IN && tokens->type <= HEREDOC))
            handle_redir(&current_cmd, &tokens);
        if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
    }
    print_simple_cmds(exec_token);
    return exec_token;
}
