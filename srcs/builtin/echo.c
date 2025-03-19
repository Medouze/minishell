/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/19 01:12:04 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void echo(char **line)
{
    int i;

    i = 1;
    if (line[1] && ft_strncmp(line[1], "-n", 3) == 0)
        i = 2;
    while (line[i])
    {
        if (line[i + 1])
            printf("%s ", line[i]);
        else
            printf("%s", line[i]);
        i++;
    }

    // Only print newline if it's not part of a pipeline and -n is not specified
    if (!(line[1] && ft_strncmp(line[1], "-n", 3) == 0) && isatty(STDOUT_FILENO))
    {
        printf("\n");
    }
}
