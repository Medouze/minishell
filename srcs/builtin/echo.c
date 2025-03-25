/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/25 13:58:37 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void echo(char **line)
{
    int i;
    int fd = STDOUT_FILENO;  // Default output file descriptor is STDOUT

    // Check if output redirection was applied
    if (line[1] && ft_strncmp(line[1], "-n", 3) == 0)
        i = 2;  // Skip the "-n" flag
    else
        i = 1;

    // Write each argument
    while (line[i])
    {
        if (line[i + 1])
            write(fd, line[i], ft_strlen(line[i]));  // Use write to avoid buffering
        else
            write(fd, line[i], ft_strlen(line[i]));  // Write without newline
        i++;
    }

    // Only print newline if it's not part of a pipeline and -n is not specified
    if (!(line[1] && ft_strncmp(line[1], "-n", 3) == 0))
    {
        write(fd, "\n", 1);  // Print newline to the redirected stdout (file)
    }
}
