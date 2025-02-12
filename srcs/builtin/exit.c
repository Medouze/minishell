/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:49 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/12 15:01:26 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exit_cmd(char **line, char **envp)
{
    int i;

    
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
            if (!(ft_isdigit(line[1][i])))
            {
                printf("exit\nminishell: %s: numeric argument required\n", line[1]);
                free(envp);
                exit(EXIT_SUCCESS);
            }
            i++;
        }
        if (line[2])
            printf("exit\nminishell: exit: too many arguments\n");
        else
        {
            free(envp);
            exit(EXIT_SUCCESS);
        }
    }
}