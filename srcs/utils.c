/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:37:39 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/02 18:14:39 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	copy_env(char **envp)
{
	t_shell	g_env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	g_env.env = malloc(sizeof(char *) * (i + 2));
	g_env.hidden_env = malloc(sizeof(char *) * (i + 2));
	if (!g_env.env || !g_env.hidden_env)
		return (g_env);
	i = 0;
	while (envp[i])
	{
		g_env.env[i] = ft_strdup(envp[i]);
		g_env.hidden_env[i] = ft_strdup(envp[i]);
		i++;
	}
	g_env.env[i] = ft_strdup("_=/usr/bin/env");
	g_env.hidden_env[i] = ft_strdup("_=/usr/bin/env");
	i++;
	g_env.env[i] = NULL;
	g_env.hidden_env[i] = NULL;
	g_env.last_exit = 0;
	return (g_env);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

void	print_error(char *error)
{
	printf("%s", error);
	exit(0);
}

void	env_cmd(char **myenv, int export)
{
	int	i;

	i = 0;
	if (export)
	{
		while (myenv[i])
		{
			printf("%s\n", myenv[i]);
			i++;
		}
	}
	else
	{
		while (myenv[i])
		{
			if (ft_strchr(myenv[i], '='))
				printf("%s\n", myenv[i]);
			i++;
		}
	}
}

int	check_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!((line[i] >= 8 && line[i] <= 13) || line[i] == 32))
			return (0);
		i++;
	}
	return (1);
}
