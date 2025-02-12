/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:33 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/12 15:01:19 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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