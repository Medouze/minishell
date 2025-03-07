/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:49 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/07 14:32:04 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	check_digit(char **line, int i, char **envp)
{
	if (!(ft_isdigit(line[1][i])))
	{
		printf("exit\nminishell: %s: numeric argument required\n", line[1]);
		free_envp(envp);
		exit(EXIT_SUCCESS);
	}
	return ;
}

void	exit_cmd(char **line, char **envp)
{
	int	i;

	if (!line[1])
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[1])
	{
		i = 0;
		while (line[1][i])
		{
			check_digit(line, i, envp);
			i++;
		}
		if (line[2])
			printf("exit\nminishell: exit: too many arguments\n");
		else
		{
			free_envp(envp);
			exit(EXIT_SUCCESS);
		}
	}
}
