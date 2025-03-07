/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/07 14:18:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_line_export(char *export)
{
	int	i;
	int	equal_count;

	i = 0;
	equal_count = 0;
	if (!(ft_isalpha(export[0]) || export[0] == '_'))
		return (0);
	i++;
	while (export[i])
	{
		if (export[i] == '=')
		{
			equal_count++;
			if (equal_count > 1)
				return (0);
		}
		else if (!(ft_isalnum(export[i])) || export[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_equal(char *export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (export[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	env_declare(char ***envp)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	while (j < i - 1)
	{
		new_env[j] = ft_strjoin("declare -x ", (*envp)[j]);
		j++;
	}
	new_env[j] = NULL;
	env_cmd(new_env);
	free_env(new_env);
}

void	add_line_env(char ***envp, char *export)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	while (j < i - 1)
	{
		new_env[j] = ft_strdup((*envp)[j]);
		j++;
	}
	new_env[j] = ft_strdup(export);
	new_env[j + 1] = ft_strdup("_=/usr/bin/env");
	new_env[j + 2] = NULL;
	free_env(*envp);
	*envp = new_env;
}

void	export_env(char **line, char ***envp, char *export)
{
	if (!line[1])
	{
		env_declare(envp);
		return ;
	}
	if (!valid_line_export(export))
	{
		printf("minishell: export: '%s': not a valid identifier\n", export);
		return ;
	}
	if (export && check_equal(export))
		add_line_env(envp, export);
}
