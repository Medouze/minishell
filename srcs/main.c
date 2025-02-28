/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/27 22:41:57 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *line;
    char    **line_split;
    t_token *tokens;
    t_shell g_env;
    (void)ac;
    (void)av;
    
    g_env = copy_env(envp);
    while (1)
    {
        line =  readline("minishell>");
        if (*line == '\0' || check_only_spaces(line))
        {
            free(line);
            continue ;
        }
        line_split = ft_split(line, 32);
        add_history(line);
        check_builtin(line_split, &g_env.env);
        tokens = lexer(line, &g_env);
        parser2(&tokens, &g_env);
        free(line);
        free_env(line_split);
    }
    return (0);
}
