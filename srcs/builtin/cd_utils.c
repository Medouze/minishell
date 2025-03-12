/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:49 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/12 15:47:41 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_old_pwd(char ***envp, char *old_pwd)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "OLDPWD=", 6) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin("OLDPWD=", old_pwd);
			return ;
		}
		i++;
	}
}

void	addto_pwd(char ***envp, char *path, char *old_pwd)
{
	int		i;
	char	*new_path;
	char	*final_path;

	i = 0;
	final_path = NULL;
	final_path = ft_strjoin("/", path);
	new_path = ft_strjoin(old_pwd, final_path);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
		{
			free((*envp)[i]);
			if (new_path[0] == '/' && new_path[1] == '/')
				(*envp)[i] = ft_strjoin("PWD=", new_path + 1);
			else
				(*envp)[i] = ft_strjoin("PWD=", new_path);
			free(new_path);
			free(final_path);
			change_old_pwd(envp, old_pwd);
			return ;
		}
		i++;
	}
}

void	change_pwd(char ***envp, char *path)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin("PWD=", path);
			return ;
		}
		i++;
	}
}

void	back_pwd(char ***envp, char *old_pwd)
{
	char	*pwd;
	char	*new_pwd;
	char	*last_slash;

	pwd = get_var(*envp, "PWD");
	last_slash = ft_strrchr(pwd, '/');
	if (!pwd || ft_strlen(pwd) == 1)
	{
		free(pwd);
		return ;
	}
	new_pwd = ft_substr(pwd, 0, last_slash - pwd);
	free(pwd);
	change_pwd(envp, new_pwd);
	change_old_pwd(envp, old_pwd);
	free(new_pwd);
}

void	back_absolute_pwd(char ***envp, char *path, char *old_pwd)
{
	char	*new_path;
	char	*tmp;
	char	*new_old_pwd;

	new_path = ft_strdup(path);
	while (1)
	{
		if (ft_strncmp(new_path, "../", 3) == 0)
		{
			back_pwd(envp, old_pwd);
			tmp = new_path;
			new_path = ft_strdup(new_path + 3);
			free(tmp);
		}
		else
			break ;
	}
	new_old_pwd = get_var(*envp, "PWD");
	if (new_path[0] != '\0')
		addto_pwd(envp, new_path, new_old_pwd);
	change_old_pwd(envp, old_pwd);
	free(new_old_pwd);
	free(new_path);
}
