/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 11:36:25 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **line)
{
	int	i;
	int	fd;

	fd = STDOUT_FILENO;
	if (line[1] && ft_strncmp(line[1], "-n", 3) == 0)
		i = 2;
	else
		i = 1;
	while (line[i])
	{
		if (line[i + 1])
		{
			write(fd, line[i], ft_strlen(line[i]));
			write(fd, " ", 1);
		}
		else
			write(fd, line[i], ft_strlen(line[i]));
		i++;
	}
	if (!(line[1] && ft_strncmp(line[1], "-n", 3) == 0))
	{
		write(fd, "\n", 1);
	}
}
