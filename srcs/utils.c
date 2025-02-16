/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:37:39 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/16 20:58:07 by mlavergn         ###   ########.fr       */
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
    while (j < i - 1)
    {
        g_env.env[j] = ft_strdup(envp[j]);
        j++;
    }
    g_env.env[j] = ft_strdup("_=/usr/bin/env");
    j++;
    g_env.env[j] = NULL;
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