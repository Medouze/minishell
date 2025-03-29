/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/28 23:59:24 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	process_line(char *line, t_shell *g_env)
{
	t_token			*lexed_token;
	t_simple_cmds	*tokens;

	if (*line == '\0' || check_only_spaces(line))
		return (1);
	add_history(line);
	lexed_token = lexer(line, g_env);
	if (!lexed_token)
		return (0);
	tokens = parser2(&lexed_token, g_env);
	if (!tokens)
	{
		free_tokens(&lexed_token);
		return (0);
	}
	execute_tokens(tokens, g_env);
	free_tokens(&lexed_token);
	free_simple_cmds(tokens);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	g_env;

	if (ac != 1)
		return (0);
	(void)av;
	ft_handler_signal(0);
	g_env = copy_env(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			free_env(g_env.env);
			free_env(g_env.hidden_env);
			break ;
		}
		if (!process_line(line, &g_env))
			free(line);
		else
			free(line);
	}
	return (0);
}
