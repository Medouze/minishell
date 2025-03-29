/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:03:32 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/28 14:18:56 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	wait_for_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	ft_handler_signal(2);
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			shell->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			shell->last_exit = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
		}
		pid = wait(&status);
	}
	ft_handler_signal(0);
}

void	handle_exec_exit(pid_t pid, t_shell *shell)
{
	int	status;

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

void	execute_command_pipe(t_simple_cmds *cmd, t_shell *shell)
{
	char	**paths;
	char	*exec_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (check_builtin(cmd->args, &shell->env, &shell->last_exit))
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
			return ;
		}
	}
	execve(exec_path, cmd->args, shell->env);
	perror("execve failed");
	exit(1);
}

char	*find_last_heredoc(t_heredoc *heredocs)
{
	t_heredoc	*current;

	current = heredocs;
	while (current)
	{
		if (current->next == NULL)
			return (current->delimiter);
		current = current->next;
	}
	return (NULL);
}
