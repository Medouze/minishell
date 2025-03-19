/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:18:06 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/19 01:08:46 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_tokens(t_simple_cmds *cmds, t_shell *shell) 
{
    int stdin_backup;
    int stdout_backup;
    while (cmds)
    {
        stdin_backup = dup(STDIN_FILENO);
        stdout_backup = handle_redirection(cmds);
        if (stdout_backup != -1)
        {
            if (cmds->next)
            {
                handle_pipe(cmds, shell);
                return ;
            }
            else
            {
                if (check_builtin(cmds->args, &shell->env))
                    ;
                else
                    execute_command(cmds, shell);
            }
            restore_stdout(stdout_backup);
            dup2(stdin_backup, STDIN_FILENO);
            close(stdin_backup);
        }
        cmds = cmds->next;
    }
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdin_backup);
    close(stdout_backup);
}

int handle_redirection(t_simple_cmds *cmd)
{
    int stdout_backup;

    stdout_backup = dup(STDOUT_FILENO);
    if (redirect_input(cmd) == -1 || redirect_output(cmd) == -1)
    {
        close(stdout_backup);
        return (-1);
    }
    return (stdout_backup);
}

void restore_stdout(int stdout_backup)
{
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
}

