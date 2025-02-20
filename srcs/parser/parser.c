/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/20 19:23:48 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_simple_cmds *init_simple_cmd()
{
    t_simple_cmds *cmd;
    
    cmd = malloc(sizeof(t_simple_cmds));
    if (!cmd)
        return (NULL);
    cmd->str = NULL;
    cmd->num_redirections = 0;
    cmd->hd_file_name = NULL;
    cmd->redirections = NULL;
    cmd->next = NULL;
    cmd->prev = NULL;
    return (cmd);
}

void add_redirection(t_simple_cmds *cmd, t_token *token)
{
    t_token *new_redir;
    t_token *last;
    
    new_redir = malloc(sizeof(t_token));
    if (!new_redir)
        return ;
    new_redir->type = token->type;
    new_redir->str = token->str;
    new_redir->next = NULL;
    if (cmd->redirections)
    {
        last = cmd->redirections;
        while (last->next)
            last = last->next;
        last->next = new_redir;
    }
    else
        cmd->redirections = new_redir;
    cmd->num_redirections++;
    if (token->type == HEREDOC)
        cmd->hd_file_name = token->str;
}

void add_argument(t_arg_node **arg_list, char *arg)
{
    t_arg_node *new_arg = malloc(sizeof(t_arg_node));
    if (!new_arg)
        return;
    new_arg->arg = arg;
    new_arg->next = NULL;

    if (!*arg_list)
        *arg_list = new_arg;
    else
    {
        t_arg_node *temp = *arg_list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_arg;
    }
}

char **convert_arg_list_to_array(t_arg_node *arg_list, int count)
{
    char **args = malloc((count + 1) * sizeof(char *));
    if (!args)
        return NULL;

    int i = 0;
    while (arg_list)
    {
        args[i++] = arg_list->arg;
        t_arg_node *temp = arg_list;
        arg_list = arg_list->next;
        free(temp);
    }
    args[i] = NULL;
    return args;
}

void print_parser(t_simple_cmds *cmds)
{
    int i;
    int cmd_index = 1;

    while (cmds)
    {
        printf("Command %d:\n", cmd_index++);
        if (cmds->str)
        {
            printf("  Arguments: ");
            for (i = 0; cmds->str[i]; i++)
                printf("\"%s\" ", cmds->str[i]);
            printf("\n");
        }
        else
            printf("  Arguments: None\n");
        if (cmds->redirections)
        {
            printf("  Redirections:\n");
            t_token *redir = cmds->redirections;
            while (redir)
            {
                printf("    Type: %d, File: \"%s\"\n", redir->type, redir->str);
                redir = redir->next;
            }
        }
        else
            printf("  Redirections: None\n");
        if (cmds->hd_file_name)
            printf("  Heredoc File: \"%s\"\n", cmds->hd_file_name);

        printf("\n");
        cmds = cmds->next;
    }
}

t_simple_cmds *parse_tokens(t_token *tokens)
{
    t_simple_cmds *head = NULL;
    t_simple_cmds *current = NULL;
    t_arg_node *arg_list = NULL;
    int arg_count = 0;

    while (tokens)
    {
        if (!current)
        {
            current = init_simple_cmd();
            if (!head)
                head = current;
        }
        if (!ft_strncmp(tokens->str, "\0", 1) == 0)
        {
            if (tokens->type == CMD)
            {
                add_argument(&arg_list, tokens->str);
                arg_count++;
            }
            else if (tokens->type == PIPE)
            {
                current->str = convert_arg_list_to_array(arg_list, arg_count);
                arg_list = NULL;
                arg_count = 0;
                current->next = init_simple_cmd();
                if (current->next)
                {
                    current->next->prev = current;
                    current = current->next;
                }
            }
            else if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT ||
                tokens->type == APPEND || tokens->type == HEREDOC)
            {
                if (tokens->next)
                {
                    add_redirection(current, tokens->next);
                    tokens = tokens->next;
                }
            }
        }
        tokens = tokens->next;
    }
    if (current)
        current->str = convert_arg_list_to_array(arg_list, arg_count);
    print_parser(head);
    return (head);
}
