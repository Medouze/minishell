/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:10 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/12 11:00:16 by mlavergn         ###   ########.fr       */
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

void    export_env(char ***envp, char* export)
{
    int i;
    int j;
    char **new_env;
    
    i = 0;
    j = 0;
    if (!check_equal(export))
        return ;
    while ((*envp)[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    while (j < i - 1)
    {
        new_env[j] = ft_strdup((*envp)[j]);
        j++;
    }
    new_env[j] = ft_strdup(export);
    j++;
    new_env[j] = ft_strdup("_=/usr/bin/env");
    j++;
    new_env[j] = NULL;
    free_env(*envp);
    *envp = new_env;
}
