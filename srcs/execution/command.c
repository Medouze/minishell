/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:22:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/11 14:58:52 by lecartuy         ###   ########.fr       */
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

void execute_command(t_simple_cmds *cmd, t_shell *shell)
{
    char **paths;
    char *exec_path;

    if (!cmd || !cmd->args || !cmd->args[0])
        return;
        
    if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
        exec_path = cmd->args[0];
    else
    {
        paths = get_paths(shell->env);
        exec_path = find_exec(cmd->args[0], paths);
        if (!exec_path)
        {
            free_tab(paths);
            print_error("Error: Command not found");
            shell->last_exit = 127;
            return;
        }
    }
    execve(exec_path, cmd->args, shell->env);
    perror("execve failed");
    shell->last_exit = 1;
    if (cmd->args[0][0] != '/' && cmd->args[0][0] != '.')
        free_tab(paths);
    _exit(1);
}


