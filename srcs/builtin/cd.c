/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:40:21 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/19 22:42:07 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_cd_home(char *path, char *current_pwd)
{
	if (!path || ft_strncmp(path, "", 1) == 0)
	{
		if (!path)
			printf("minishell: cd: HOME not set\n");
		free(current_pwd);
		free(path);
		return ;
	}
}

void	handle_cd_oldpwd(char ***envp, char *path, char *current_pwd)
{
	char	*previous_pwd;

	previous_pwd = get_var(*envp, "OLDPWD");
	if (!previous_pwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		free(current_pwd);
		free(path);
		return ;
	}
	if (chdir(previous_pwd) == -1)
		printf("minishell: cd: %s: No such file or directory\n", previous_pwd);
	else
		change_pwd(envp, previous_pwd);
	free(current_pwd);
	free(previous_pwd);
	free(path);
}

void	process_cd_path(char ***envp, char *path, char *current_pwd)
{
	if (ft_strncmp(path, "..", 2) == 0)
	{
		if (ft_strncmp(path, "../", 3) == 0)
			back_absolute_pwd(envp, path, current_pwd);
		else
			back_pwd(envp, current_pwd);
	}
	else if (ft_strncmp(path, ".", 1) == 0)
	{
		free(current_pwd);
		free(path);
		return ;
	}
	else if (path[0] == '/')
		change_pwd(envp, path);
	else
		addto_pwd(envp, path, current_pwd);
	free(current_pwd);
	free(path);
}

void	define_path_currentpwd(char ***envp, char **line,
	char **path, char **pwd)
{
	*pwd = get_var(*envp, "PWD");
	if (line[1])
		*path = ft_strdup(line[1]);
	else
		*path = get_var(*envp, "HOME");
	handle_cd_home(*path, *pwd);
}

void	cd_cmd(char **line, char ***envp)
{
	char	*current_pwd;
	char	*path;

	if (line[1] && line[2])
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	define_path_currentpwd(envp, line, &path, &current_pwd);
	if (ft_strncmp(path, "-", 1) == 0)
	{
		handle_cd_oldpwd(envp, path, current_pwd);
		return ;
	}
	if (line[1])
		remove_slash(&path);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		free(current_pwd);
		free(path);
		return ;
	}
	process_cd_path(envp, path, current_pwd);
}
