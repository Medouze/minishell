/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:46 by lecartuy          #+#    #+#             */
/*   Updated: 2025/04/03 16:38:15 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_child(t_simple_cmds *cmd, t_pipe_data *p_data, t_shell *shell)
{
	int	i;

	i = 0;
	ft_handler_signal(3);
	if (redirect_input(cmd, shell) == -1)
		exit(1);
	if (p_data->index > 0)
		dup2(p_data->pipe_fd[p_data->index - 1][0], STDIN_FILENO);
	if (redirect_output(cmd) == -1)
		exit(EXIT_FAILURE);
	if (p_data->index < p_data->num_pipes)
		dup2(p_data->pipe_fd[p_data->index][1], STDOUT_FILENO);
	while (i < p_data->num_pipes)
	{
		close(p_data->pipe_fd[i][0]);
		close(p_data->pipe_fd[i][1]);
		i++;
	}
	execute_command_pipe(cmd, shell);
	exit(EXIT_SUCCESS);
}

void	launch_child_process(t_simple_cmds *cmd,
							t_pipe_data *p_data, t_shell *shell)
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
		execute_child(cmd, p_data, shell);
		exit(EXIT_FAILURE);
	}
}

static void	execute_pipeline(t_simple_cmds *cmds,
							int (*pipe_fd)[2], int num_pipes, t_shell *shell)
{
	int				i;
	t_simple_cmds	*current;
	t_pipe_data		p_data;

	i = 0;
	current = cmds;
	while (current)
	{
		p_data.pipe_fd = pipe_fd;
		p_data.index = i;
		p_data.num_pipes = num_pipes;
		launch_child_process(current, &p_data, shell);
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
	int	(*pipe_fd)[2];

	num_pipes = count_pipes(cmds);
	pipe_fd = malloc(sizeof(int [num_pipes][2]));
	if (!pipe_fd)
	{
		shell->last_exit = 1;
		print_error("Error: Memory allocation failed");
		return ;
	}
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			shell->last_exit = 1;
			free(pipe_fd);
			return ;
		}
		i++;
	}
	execute_pipeline(cmds, pipe_fd, num_pipes, shell);
	free(pipe_fd);
}
