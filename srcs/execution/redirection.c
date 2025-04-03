/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/04/03 15:48:00 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_heredoc(t_simple_cmds *cmd, t_shell *shell)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	if (read_heredoc_input(pipe_fd[1], cmd, shell) == -1)
		return (-1);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 for heredoc failed");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

int	redirect_input(t_simple_cmds *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening input file");
			shell->last_exit = 1;
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 for input failed");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	redirect_output(t_simple_cmds *cmd)
{
	int			fd;
	t_outfile	*out;

	out = cmd->outfiles;
	while (out)
	{
		if (out->append)
			fd = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Failed to open output file");
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 for output failed");
			close(fd);
			return (-1);
		}
		close(fd);
		out = out->next;
	}
	return (0);
}

int	handle_redirection(t_simple_cmds *cmd, t_shell *shell)
{
	if (redirect_input(cmd, shell) == -1)
		return (-1);
	if (redirect_output(cmd) == -1)
	{
		shell->last_exit = 1;
		return (-1);
	}
	return (0);
}
