/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/11 15:22:21 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *line;
    int stdout_backup;
    t_token *lexed_token;
    t_simple_cmds   *tokens;
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
        add_history(line);
        lexed_token = lexer(line, &g_env);
        if (!lexed_token)
        {
            free(line);
            free_tokens(&lexed_token);
            free_simple_cmds(tokens);
            continue ;
        }
        tokens = parser2(&lexed_token, &g_env);
        if (!tokens)
        {
            free(line);
            free_tokens(&lexed_token);
            free_simple_cmds(tokens);
            continue ;
        }
        stdout_backup = handle_redirection(tokens);
        if (stdout_backup != -1)
        {
            if (!check_builtin(tokens->args, &g_env.env))
                execute_tokens(tokens, &g_env);
            restore_stdout(stdout_backup);
        }
        free(line);
        free_tokens(&lexed_token);
        free_simple_cmds(tokens);
    }
    return (0);
}
