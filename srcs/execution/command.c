/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:22:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/02/19 15:42:29 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **get_paths(char **env) 
{
    while (*env) 
    {
        if (ft_strncmp(*env, "PATH=", 5) == 0)
            return (ft_split(*env + 5, ':'));
        env++;
    }
    return (NULL);
}

static  char *find_exec(t_token *token, char **paths) 
{
    char *path;
    char *full_path;

    if (!token || !token->str)
        return (NULL);
    if (ft_strncmp(token->str, "./", 2) == 0 && access(token->str, X_OK) == 0)
        return (ft_strdup(token->str));
    while (*paths) 
    {
        path = ft_strjoin(*paths, "/");
        full_path = ft_strjoin(path, token->str);
        free(path);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        paths++;
    }
    return (NULL);
}

static  char **get_cmd_args(t_token *token)
{
    int count;
    t_token *tmp;
    char **args;
    int i;

    count = 0;
    tmp = token;
    while (tmp && tmp->type == CMD) 
    {
        count++;
        tmp = tmp->next;
    }
    args = malloc((count + 1) * sizeof(char *));
    if (!args)
        return (NULL);
    i = 0;
    while (token && token->type == CMD) 
    {
        args[i] = ft_strdup(token->str);
        i++;
        token = token->next;
    }
    args[i] = NULL;
    return (args);
}

void execute_command(t_token *token, char **env)
{
    char **args;
    char **paths;
    char *exec_path;

    if (!token || token->type != CMD)
        return;
    args = get_cmd_args(token);
    paths = get_paths(env);
    exec_path = find_exec(args[0], paths);
    if (!exec_path)
    {
        free_tab(args);
        free_tab(paths);
        print_error("Error: Command not found");
    }
    execve(exec_path, args, env);
    perror("execve failed");
    free_tab(args);
    free_tab(paths);
    exit(0);
}

