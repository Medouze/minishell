/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:33:22 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/12 12:29:43 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     valid_line_unset(char *unset)
{
    int i;

    i = 0;
    if (!(ft_isalpha(unset[0]) || unset[0] == '_'))
        return (0);
    i++;
    while (unset[i])
    {
        if (!(ft_isalnum(unset[i])) || unset[i] == '_')
            return (0);
        i++;  
    }
    return (1);
}

int     find_line_unset(char ***envp, char *unset)
{
    int unset_line;
    
    unset_line = 0;
    
    while ((*envp)[unset_line])
    {
        if (ft_strncmp((*envp)[unset_line], unset, ft_strlen(unset)) == 0)
            return (unset_line);
        unset_line++;
    }
    return (0);
}

void    unset_env(char **line, char ***envp, char *unset)
{
    int line_unset;

    if (!line[1])
        return ;
    if (!valid_line_unset(unset))
    {
        printf("minishell: unset: '%s': not a valid identifier\n", unset);
        return ;
    }
    unset = ft_strjoin(unset, "=");
    if (!(line_unset = find_line_unset(envp, unset)))
        return ;
}