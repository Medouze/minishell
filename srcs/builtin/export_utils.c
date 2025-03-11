/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:45:55 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/11 14:48:50 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_key(char *line)
{
	char	*equal_sign;

	equal_sign = ft_strchr(line, '=');
	if (!equal_sign)
		return (ft_strdup(line));
	return (ft_substr(line, 0, equal_sign - line));
}

int	replace_line(char ***envp, char *line)
{
	int		i;
	char	*key;

	if (!envp || !*envp || !line)
		return (0);
	key = extract_key(line);
	if (!key)
		return (0);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0 &&
			((*envp)[i][ft_strlen(key)] == '='
				|| (*envp)[i][ft_strlen(key)] == '\0'))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(line);
			free(key);
			return (1);
		}
		i++;
	}
	free(key);
	return (0);
}
