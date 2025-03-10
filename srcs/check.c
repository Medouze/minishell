/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/10 17:14:39 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    check_builtin(char **line, char ***envp)
{
    if (ft_strncmp(line[0], "echo", 5) == 0)
        echo(line);
    if (ft_strncmp(line[0], "pwd", 4) == 0)
        pwd(*envp);
    if (ft_strncmp(line[0], "exit", 5) == 0)
        exit_cmd(line, *envp);
    if (ft_strncmp(line[0], "env", 4) == 0)
        env_cmd(*envp, 0);
    if (ft_strncmp(line[0], "export", 7) == 0)
        export_env(line, envp, line[1]);
    if (ft_strncmp(line[0], "unset", 6) == 0)
        unset_env(line, envp, line[1]);
    if (ft_strncmp(line[0], "cd", 3) == 0)
        cd_cmd(line, envp);
}
