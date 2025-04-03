/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:18:06 by lecartuy          #+#    #+#             */
/*   Updated: 2025/04/03 16:37:33 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	restore_fds(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

static int	backup_fds(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
	{
		perror("Failed to backup fds");
		return (-1);
	}
	return (0);
}

static int	execute_command_builtin(t_simple_cmds *cmds, t_shell *shell)
{
	if (cmds->args && cmds->args[0])
	{
		if (check_builtin(cmds->args, &shell->env, &shell->last_exit))
			return (1);
		execute_command(cmds, shell);
	}
	return (0);
}

static int	handle_heredocs_and_backup(t_simple_cmds *cmds, t_shell *shell,
		int *stdin_backup, int *stdout_backup)
{
	if (backup_fds(stdin_backup, stdout_backup) == -1)
		return (0);
	if (cmds->heredocs)
	{
		if (handle_heredoc(cmds, shell) == -1)
		{
			restore_fds(*stdin_backup, *stdout_backup);
			return (0);
		}
	}
	return (1);
}

void	execute_tokens(t_simple_cmds *cmds, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

	while (cmds)
	{
		if (!handle_heredocs_and_backup(cmds, shell, &stdin_backup,
				&stdout_backup))
			return ;
		if (cmds->next)
		{
			handle_pipe(cmds, shell);
			restore_fds(stdin_backup, stdout_backup);
			return ;
		}
		if (handle_redirection(cmds, shell) != -1)
		{
			if (execute_command_builtin(cmds, shell))
				return (restore_fds(stdin_backup, stdout_backup));
			restore_fds(stdin_backup, stdout_backup);
		}
		ft_handler_signal(0);
		restore_fds(stdin_backup, stdout_backup);
		cmds = cmds->next;
	}
}
