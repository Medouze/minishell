/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/11 14:47:03 by mlavergn         ###   ########.fr       */
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

char	*add_quotes_env(char *envp)
{
	int		i;
	int		j;
	int		has_equal;
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(envp) + 3));
	i = 0;
	j = 0;
	has_equal = 0;
	while (envp[i])
	{
		if (envp[i] == '=' && !has_equal)
		{
			new_str[j++] = envp[i++];
			new_str[j++] = '\"';
			has_equal = 1;
			continue ;
		}
		new_str[j++] = envp[i++];
	}
	if (has_equal)
		new_str[j++] = '\"';
	new_str[j] = '\0';
	return (new_str);
}

void	env_declare(char ***envp)
{
	int		i;
	int		j;
	char	**new_env;
	char	*quoted_env;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	while (j < i - 1)
	{
		quoted_env = add_quotes_env((*envp)[j]);
		new_env[j] = ft_strjoin("declare -x ", quoted_env);
		free(quoted_env);
		j++;
	}
	new_env[j] = NULL;
	env_cmd(new_env, 1);
	free_env(new_env);
}

void	add_line_env(char ***envp, char *export)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (replace_line(envp, export) == 1)
		return ;
	else
	{
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
	if (export)
		add_line_env(envp, export);
}
