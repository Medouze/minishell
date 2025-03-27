/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:20:31 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 16:52:32 by mlavergn         ###   ########.fr       */
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
    pid_t pid;
    int status;

    exec_path = NULL;
    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
        exec_path = cmd->args[0];
    else
    {
        paths = get_paths(shell->env);
        if (!paths)
            return ;
        exec_path = find_exec(cmd->args[0], paths);
        if (!exec_path)
        {
            free_tab(paths);
            perror("Error: Command not found");
            shell->last_exit = 127;
            return;
        }
    }

    pid = fork();
    if (pid == 0)
    {   
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (redirect_output(cmd) == -1)
            exit(1);
        fprintf(stderr, "execution of command...\n");
        execve(exec_path, cmd->args, shell->env);
        perror("execve failed");
        exit(1);
    }
    else if (pid > 0)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status))
        {
            shell->last_exit = 128 + WTERMSIG(status);
            if (WTERMSIG(status) == SIGINT)
                write(STDOUT_FILENO, "\n", 1);
        }
        else if (WIFEXITED(status))
            shell->last_exit = WEXITSTATUS(status);
    }
    else
        perror("fork failed");
    if (exec_path != cmd->args[0])
        free(exec_path);
    if (cmd->args[0][0] != '/' && cmd->args[0][0] != '.')
        free_tab(paths);
}

void execute_command_pipe(t_simple_cmds *cmd, t_shell *shell)
{
    char **paths;
    char *exec_path;
    
    if (!cmd || !cmd->args || !cmd->args[0])
        return;
    if (check_builtin(cmd->args, &shell->env))
        return ;
    if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
        exec_path = cmd->args[0];
    else
    {
        paths = get_paths(shell->env);
        exec_path = find_exec(cmd->args[0], paths);
        if (!exec_path)
        {
            free_tab(paths);
            print_error("Error: Command not found\n");
            shell->last_exit = 127;
            return;
        }
    }
    execve(exec_path, cmd->args, shell->env);
    perror("execve failed");
    exit(1);
}





