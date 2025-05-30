/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 17:06:25 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_echo_pwd_exit(char **line, char ***envp, int *last_exit)
{
	if (ft_strncmp(line[0], "echo", 5) == 0)
	{
		echo(line);
		*last_exit = 0;
		return (1);
	}
	if (ft_strncmp(line[0], "pwd", 4) == 0)
	{
		pwd(*envp);
		*last_exit = 0;
		return (1);
	}
	if (ft_strncmp(line[0], "exit", 5) == 0)
	{
		exit_cmd(line, *envp, last_exit);
		return (1);
	}
	return (0);
}

int	check_env_export_unset(char **line, char ***envp, int *last_exit)
{
	if (ft_strncmp(line[0], "env", 4) == 0)
	{
		env_cmd(*envp, 0);
		*last_exit = 0;
		return (1);
	}
	if (ft_strncmp(line[0], "export", 7) == 0)
	{
		export_env(line, envp, line[1], last_exit);
		return (1);
	}
	if (ft_strncmp(line[0], "unset", 6) == 0)
	{
		unset_env(line, envp, line[1], last_exit);
		return (1);
	}
	return (0);
}

int	check_cd(char **line, char ***envp, int *last_exit)
{
	if (ft_strncmp(line[0], "cd", 3) == 0)
	{
		if (!cd_cmd(line, envp))
			*last_exit = 1;
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

int	check_builtin(char **line, char ***envp, int *last_exit)
{
	if (check_echo_pwd_exit(line, envp, last_exit)
		|| check_env_export_unset(line, envp, last_exit)
		|| check_cd(line, envp, last_exit))
		return (1);
	return (0);
}
