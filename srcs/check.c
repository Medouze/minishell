/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/11 15:09:03 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     check_spaces(char *line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            return (1);
        i++;
    }
    return (0);
}

void    check_builtin(char **line, char **envp)
{
    if (ft_strncmp(line[0], "echo", 5) == 0)
        echo(line);
    if (ft_strncmp(line[0], "pwd", 4) == 0)
        pwd(envp);
    if (ft_strncmp(line[0], "exit", 5) == 0)
    {
        printf("exit\n");
        exit(EXIT_SUCCESS);
    }
}
