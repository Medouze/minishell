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

int	check_digit(char **line, int i, char **envp)
{
	int	exit_status;

	if (!(ft_isdigit(line[1][i])))
	{
		printf("exit\nminishell: %s: numeric argument required\n", line[1]);
		free_envp(envp);
		exit(EXIT_SUCCESS);
	}
	exit_status = ft_atoi(line[1]);
	return (exit_status);
}

void	exit_cmd(char **line, char **envp, int *last_exit)
{
	int	i;

	if (!line[1])
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line[2])
	{
		*last_exit = 1;
		printf("exit\nminishell: exit: too many arguments\n");
		return ;
	}
	if (line[1])
	{
		i = 0;
		while (line[1][i])
		{
			*last_exit = check_digit(line, i, envp);
			i++;
		}
		free_envp(envp);
		exit(EXIT_SUCCESS);
	}
}
