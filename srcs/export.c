/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:10 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/12 11:25:27 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     check_equal(char *export)
{
    int i;

    i = 0;
    while (export[i])
    {
        if (export[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void    env_declare(char ***envp)
{
    int     i;
    int     j;
    char    **new_env;
    
    i = 0;
    j = 0;
    while ((*envp)[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    while (j < i)
    {
        new_env[j] = ft_strjoin("declare -x ", (*envp)[j]);
        j++;
    }
    new_env[j] = NULL;
    env_cmd(new_env);
}

void    export_env(char **line, char ***envp, char *export)
{
    int i;
    int j;
    char **new_env;
    
    i = 0;
    j = 0;
    if (!line[1])
        env_declare(envp);
    if (export && check_equal(export))
    {
        while ((*envp)[i])
            i++;
        new_env = malloc(sizeof(char *) * (i + 2));
        while (j < i - 1)
        {
            new_env[j] = ft_strdup((*envp)[j]);
            j++;
        }
        new_env[j] = ft_strdup(export);
        new_env[j + 1] = ft_strdup("_=/usr/bin/env");
        new_env[j + 2] = NULL;
        free_env(*envp);
        *envp = new_env;
    }
}
