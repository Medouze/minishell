/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:20:31 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/03 15:33:42 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (ft_split(*env + 5, ':'));
		env++;
	}
	return (NULL);
}

char	*find_exec(char *cmd, char **paths)
{
	char	*path;
	char	*full_path;

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

static char	*get_exec_path(t_simple_cmds *cmd, t_shell *shell)
{
	char	**paths;
	char	*exec_path;

	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		return (cmd->args[0]);
	paths = get_paths(shell->env);
	if (!paths)
	{
		printf("minishell: No such file or directory\n");
		return (NULL);
	}
	exec_path = find_exec(cmd->args[0], paths);
	if (!exec_path)
	{
		free_tab(paths);
		write(2, "Error: Command not found\n", 25);
		shell->last_exit = 127;
		return (NULL);
	}
	free_tab(paths);
	return (exec_path);
}

static void	launch_exec(char *exec_path, t_simple_cmds *cmd, t_shell *shell)
{
	execve(exec_path, cmd->args, shell->env);
	if (errno == EACCES)
	{
		if (cmd->args[0][0] == '\0')
		{
			write(2, "Command not found\n", 18);
			exit(127);
		}
		else
		{
			write(2, "Permission denied\n", 18);
			exit(126);
		}
	}
	else if (errno == ENOENT)
		exit(127);
	else
		exit(1);
}

void	execute_command(t_simple_cmds *cmd, t_shell *shell)
{
	char	*exec_path;
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	exec_path = get_exec_path(cmd, shell);
	if (!exec_path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		launch_exec(exec_path, cmd, shell);
	}
	else if (pid > 0)
		handle_exec_exit(pid, shell);
	else
		perror("fork failed");
	if (exec_path != cmd->args[0])
		free(exec_path);
}
