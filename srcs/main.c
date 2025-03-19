/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/19 22:16:17 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_flag = 0;

int main(int ac, char **av, char **envp)
{
    char    *line;
    t_token *lexed_token;
    t_simple_cmds *tokens;
    t_shell g_env;

    (void)ac;
    (void)av;

    // Set up signal handling for the shell
    ft_handler_signal(0); // 0 for default shell behavior

    g_env = copy_env(envp);
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line == '\0' || check_only_spaces(line))
        {
            free(line);
            continue;
        }
        add_history(line);
        lexed_token = lexer(line, &g_env);
        if (!lexed_token)
        {
            free(line);
            continue;
        }
        tokens = parser2(&lexed_token, &g_env);
        if (!tokens)
        {
            free(line);
            free_tokens(&lexed_token);
            continue;
        }
        execute_tokens(tokens, &g_env);
        free(line);
        free_tokens(&lexed_token);
        free_simple_cmds(tokens);
    }

    return (0);
}

