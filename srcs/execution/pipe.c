/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:46 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/28 19:06:58 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child(t_simple_cmds *cmd, int pipe_fd[][2], int index, int num_pipes, t_shell *shell)
{
	int	i;

	i = 0;
	ft_handler_signal(3);
	if (redirect_input(cmd, shell) == -1)
		exit(EXIT_FAILURE);
	else if (index > 0)
		dup2(pipe_fd[index - 1][0], STDIN_FILENO);
	if (redirect_output(cmd) == -1)
		exit(EXIT_FAILURE);
	else if (index < num_pipes)
		dup2(pipe_fd[index][1], STDOUT_FILENO);
	while (i < num_pipes)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
	execute_command_pipe(cmd, shell);
	exit(EXIT_SUCCESS);
}

static void	launch_child_process(t_simple_cmds *cmd, int pipe_fd[][2], int index, int num_pipes, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		shell->last_exit = 1;
		print_error("Error: Fork failed");
		return ;
	}
	if (pid == 0)
	{
		execute_child(cmd, pipe_fd, index, num_pipes, shell);
		exit(EXIT_FAILURE);
	}
}

static void	execute_pipeline(t_simple_cmds *cmds, int pipe_fd[][2], int num_pipes, t_shell *shell)
{
	int				i;
	t_simple_cmds	*current;

	i = 0;
	current = cmds;
	while (current)
	{
		launch_child_process(current, pipe_fd, i, num_pipes, shell);
		current = current->next;
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
	wait_for_children(shell);
}

static int	count_pipes(t_simple_cmds *cmds)
{
	int	count;

	count = 0;
	while (cmds->next)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	handle_pipe(t_simple_cmds *cmds, t_shell *shell)
{
	int	num_pipes;
	int	i;

	num_pipes = count_pipes(cmds);
	int	pipe_fd[num_pipes][2];

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			shell->last_exit = 1;
			print_error("Error: Pipe creation failed");
			return ;
		}
		i++;
	}
	execute_pipeline(cmds, pipe_fd, num_pipes, shell);
}
