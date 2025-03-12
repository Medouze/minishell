/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:45:47 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/12 15:48:49 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_slash(char **line)
{
	size_t	len;

	if (line == NULL || *line == NULL)
		return ;
	len = ft_strlen(*line);
	if (len > 0 && (*line)[len - 1] == '/')
		(*line)[len - 1] = '\0';
}

char	*get_var(char **envp, char *line)
{
	int		i;
	char	*pwd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], line, ft_strlen(line)) == 0)
		{
			pwd = ft_strdup(envp[i] + ft_strlen(line) + 1);
			return (pwd);
		}
		i++;
	}
	printf("Couldnt find PATH\n");
	return (NULL);
}
