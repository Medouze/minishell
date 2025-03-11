/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:18:06 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/11 15:19:08 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_tokens(t_simple_cmds *cmds, t_shell *shell)
{
    while (cmds)
    {
        if (cmds->next)
            handle_pipe(cmds, shell);
        else
            execute_command(cmds, shell); 
        cmds = cmds->next;
    }
}

int handle_redirection(t_simple_cmds *cmd)
{
    int stdout_backup;

    stdout_backup = dup(STDOUT_FILENO); // Save original stdout
    if (redirect_input(cmd) == -1 || redirect_output(cmd) == -1)
    {
        close(stdout_backup);
        return (-1);
    }
    return (stdout_backup);
}

void restore_stdout(int stdout_backup)
{
    dup2(stdout_backup, STDOUT_FILENO); // Restore original stdout
    close(stdout_backup);
}

