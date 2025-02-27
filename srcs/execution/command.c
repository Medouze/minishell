/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:22:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/02/27 15:17:15 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void free_tab(char **tab)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

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

static char *find_exec(char *cmd, char **paths) 
{
    char *path;
    char *full_path;

    if (!cmd)
        return (NULL);
    if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    while (*paths) 
    {
        path = ft_strjoin(*paths, "/");
        full_path = ft_strjoin(path, cmd);
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
        exit(EXIT_FAILURE);
    }
    execve(exec_path, args, env);
    perror("execve failed");
    free_tab(args);
    free_tab(paths);
    exit(0);
}


