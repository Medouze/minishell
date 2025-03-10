/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:37:39 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/10 17:14:21 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell copy_env(char **envp)
{
    t_shell g_env;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    while (envp[i])
        i++;
    g_env.env = malloc(sizeof(char *) * (i + 1));
    g_env.hidden_env = malloc(sizeof(char *) * (i + 1));
    while (j < i - 1)
    {
        g_env.env[j] = ft_strdup(envp[j]);
        j++;
    }
    g_env.env[j] = ft_strdup("_=/usr/bin/env");
    j++;
    g_env.env[j] = NULL;
    g_env.last_exit = 0;
    i = 0;
    while (g_env.env[i])
    {
        g_env.hidden_env[i] = ft_strdup(g_env.env[i]);
        i++;
    }
    g_env.hidden_env[i] = NULL;
    return (g_env);
}

void    free_env(char **env)
{
    int i;
    
    i = 0;
    if (env)
    {
        while (env[i])
        {
            free(env[i]);
            i++;
        }
        free(env);
    }
}

void    print_error(char *error)
{
    printf("%s", error);
    exit(0);
}

void    env_cmd(char **myenv, int export)
{
    int i;

    i = 0;
    if (export)
    {
        while (myenv[i])
        {
            printf("%s\n", myenv[i]);
            i++;
        }
    }
    else
    {
        while (myenv[i])
        {
            if (ft_strchr(myenv[i] , '='))
                printf("%s\n", myenv[i]);
            i++;
        }
    }
}

int check_only_spaces(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!((line[i] >= 8 && line[i] <= 13) || line[i] == 32 || line[i] == '\"' || line[i] == '\''))
           return (0);
        i++; 
    }
    return (1);
}