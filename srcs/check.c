/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/12 21:32:16 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_builtin(char **line, char ***envp)
{
    if (ft_strncmp(line[0], "echo", 5) == 0)
    {
        echo(line);
        return (1);
    }
    if (ft_strncmp(line[0], "pwd", 4) == 0)
    {
        pwd(*envp);
        return (1);
    }
    if (ft_strncmp(line[0], "exit", 5) == 0)
    {
        exit_cmd(line, *envp);
        return (1);
    }
    if (ft_strncmp(line[0], "env", 4) == 0)
    {
        env_cmd(*envp, 0);
        return (1);
    }
    if (ft_strncmp(line[0], "export", 7) == 0)
    {
        export_env(line, envp, line[1]);
        return (1);
    }
    if (ft_strncmp(line[0], "unset", 6) == 0)
    {
        unset_env(line, envp, line[1]);
        return (1);
    }
    if (ft_strncmp(line[0], "cd", 3) == 0)
    {
        cd_cmd(line, envp);
        return (1);
    }
    return (0);
}

