/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/13 22:37:04 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_flag = 0;

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_signal_flag = 1;
        // Reset readline's state

        write(STDOUT_FILENO, "\n", 1); // Use `write` to ensure it's async-signal-safe
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();        // Redraw the prompt
    }
    else if (sig == SIGQUIT)
    {
        write(1, "QUIT 3\n", 8);  // Custom handling for Ctrl+\ if needed
    }
}

int main(int ac, char **av, char **envp)
{
    char    *line;
    t_token *lexed_token;
    t_simple_cmds   *tokens;
    t_shell g_env;

    (void)ac;
    (void)av;
    
    g_env = copy_env(envp);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        if (g_signal_flag)
        {
            g_signal_flag = 0;
            write(STDOUT_FILENO, "\n", 1); // Print a newline
            rl_on_new_line();
            rl_replace_line("", 0);
            continue ;
        }
        line = readline("minishell>");
        if (!line)
        {
            printf("exit\n");
            break ;
        }
        if (*line == '\0' || check_only_spaces(line)) // Handle empty line or spaces
        {
            free(line);
            continue ;
        }

        add_history(line);  // Add the input to history
        lexed_token = lexer(line, &g_env);  // Tokenize the input
        if (!lexed_token)
        {
            free(line);
            free_tokens(&lexed_token);
            continue ;
        }
        
        tokens = parser2(&lexed_token, &g_env);  // Parse the tokens
        if (!tokens)
        {
            free(line);
            free_tokens(&lexed_token);
            free_simple_cmds(tokens);
            continue ;
        }

        execute_tokens(tokens, &g_env);  // Execute the tokens
        free(line);
        free_tokens(&lexed_token);
        free_simple_cmds(tokens);
    }
    return (0);
}
