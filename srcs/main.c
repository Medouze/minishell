/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/20 20:43:03 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *line;
    t_shell g_env;
    char    **line_split;
    (void)ac;
    (void)av;
    
    g_env = copy_env(envp);
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
        check_builtin(line_split, &g_env.env);
        parse_tokens(lexer(line));
        free(line);
        free_env(line_split);
    }
    return (0);
}
