/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:57:07 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/25 16:44:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <readline/history.h>

typedef enum e_type
{
	CMD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	**env;
	int		last_exit;
}	t_shell;

typedef struct s_arg_node
{
    char                *arg;
    struct s_arg_node   *next;
} t_arg_node;

typedef struct s_simple_cmds
{
	char **str;
	int num_redirections;
	char *hd_file_name;
	t_token *redirections;
	struct s_simple_cmds *next;
	struct s_simple_cmds *prev;
} t_simple_cmds;

/*checks*/
void    check_builtin(char **line, char ***envp);
char	*check_cmd(char *cmd, char **envp);

/*built in*/
void    echo(char **line);
void    pwd(char **envp);
void    exit_cmd(char **line, char **envp);
void    env_cmd(char **myenv);
void    export_env(char **line, char ***envp, char* export);
void    unset_env(char **line, char ***envp, char *unset);
void    cd_cmd(char **line, char ***envp);

/*utils*/
t_shell	copy_env(char **envp);
void    free_env(char **env);
void	print_error(char *error);

/*lexer*/
t_token *lexer(char *str);
void	handle_token(char *str, t_token **head, t_token **current, int *i);
t_token *new_token(t_type type, char *str);
void    fill_token(t_token **head, t_token **current, t_token *new);
void	free_tokens(t_token *head);
void	handle_quotes(char *str, int *i, t_token **current, t_token **head);
void	print_tokens(t_token *head); //delete plus tard

/*parser*/
void	print_parser(t_simple_cmds *cmds);
void 	parse_tokens(t_token *tokens);
void	parser2(t_token **tokens, char **env);
void	remove_quotes(char **str);
void	expand_dollar(char	**str, char **env);

/*execution*/
void execute_command(t_token *token, char **env);
void execute_tokens(t_token *tokens, t_shell *shell);
void handle_pipe(t_token *tokens, char **env);
void handle_redirection(t_token *token);

#endif