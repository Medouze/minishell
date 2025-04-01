/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:33:22 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/07 14:17:25 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_line_unset(char ***envp, char *unset)
{
	int	unset_line;

	unset_line = 0;
	while ((*envp)[unset_line])
	{
		if (ft_strncmp((*envp)[unset_line], unset, ft_strlen(unset)) == 0)
			return (unset_line);
		unset_line++;
	}
	return (0);
}

void	remove_line_env(char ***envp, int line_unset)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	while ((*envp)[i])
	{
		if (i == line_unset)
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup((*envp)[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_env(*envp);
	*envp = new_env;
}

void	unset_env(char **line, char ***envp, char *unset, int *last_exit)
{
	int	line_unset;

	if (!line[1])
		return ;
	unset = ft_strjoin(unset, "=");
	line_unset = find_line_unset(envp, unset);
	if (!line_unset)
	{
		*last_exit = 1;
		printf("minishell: %s: event not found\n", unset);
		free(unset);
		return ;
	}
	remove_line_env(envp, line_unset);
	free(unset);
}
