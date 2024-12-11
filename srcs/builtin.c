/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:26:32 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/11 15:07:21 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    echo(char **line)
{
    int i;
    
    i = 1;
    if (line[1] && ft_strncmp(line[1], "-n", 3) == 0)
        i = 2;
    while (line[i])
    {
        if (line[i + 1])
            printf("%s ",line[i]);
        else
            printf("%s",line[i]);
        i++;
    }
    if (!(line[1] && ft_strncmp(line[1], "-n", 3) == 0))
        printf("\n");
}

void    pwd(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD", 3) == 0)
            printf("%s\n", envp[i] + 4);
        i++;
    }
}

