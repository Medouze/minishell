/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/16 19:47:13 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *line;
    char    **myenv;
    char    **line_split;
    (void)ac;
    (void)av;
    
    myenv = copy_env(envp);
    while (1)
    {
        line =  readline("minishell>");
        if (*line == '\0')
        {
            free(line);
            continue;
        }
        add_history(line);
        line_split = ft_split(line, ' ');
        check_builtin(line_split, &myenv);
        lexer(line);
        free(line);
        free_env(line_split);
    }
    return (0);
}
