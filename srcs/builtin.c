/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:26:32 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/11 16:49:48 by mlavergn         ###   ########.fr       */
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
        if (ft_strncmp(envp[i], "PWD=", 4) == 0)
        {
            printf("%s\n", envp[i] + 4);
            return ;
        }
        i++;
    }
}

void    exit_cmd(char **line)
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
                exit(EXIT_SUCCESS);
            }
            i++;
        }
        if (line[2])
            printf("exit\nminishell: exit: too many arguments\n");
        else
            exit(EXIT_SUCCESS);
    }
}

void    env_cmd(char **myenv)
{
    int i;

    i = 0;
    while (myenv[i])
    {
        printf("%s\n", myenv[i]);
        i++;
    }
}
