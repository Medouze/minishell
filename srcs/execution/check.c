/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 16:53:41 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_echo_pwd_exit(char **line, char ***envp)
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
	return (0);
}

int	check_env_export_unset(char **line, char ***envp)
{
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
	return (0);
}

int	check_cd(char **line, char ***envp)
{
	if (ft_strncmp(line[0], "cd", 3) == 0)
	{
		cd_cmd(line, envp);
		return (1);
	}
	return (0);
}

int	path_exist(char **env) 
{
    while (*env) 
    {
        if (ft_strncmp(*env, "PATH=", 5) == 0)
            return (1);
        env++;
    }
    return (0);
}

int	check_builtin(char **line, char ***envp)
{
	if (!path_exist(*envp) && ft_strncmp(line[0], "export", 7))
		printf("minishell: No such file or directory\n");
	if (check_echo_pwd_exit(line, envp)
		|| check_env_export_unset(line, envp) || check_cd(line, envp))
	{
		if (!path_exist(*envp))
			return (2);
		return (1);
	}
	return (0);
}
