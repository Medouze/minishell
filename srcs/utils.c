/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:37:39 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/11 17:48:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **copy_env(char **envp)
{
    char    **my_env;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    while (envp[i])
        i++;
    my_env = malloc(sizeof(char *) * (i + 1));
    while (j < i - 1)
    {
        my_env[j] = ft_strdup(envp[j]);
        j++;
    }
    my_env[j] = ft_strdup("_=/usr/bin/env");
    j++;
    my_env[j] = NULL;
    return (my_env);
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
