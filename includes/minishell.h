/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:57:07 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/07 14:07:09 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <fcntl.h>

#ifndef SPE_CHARS
# define SPE_CHARS "!#$%&()*+,-./:;<=>?@[\\]^_`{|}~"
#endif

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
    char    **args;       // Arguments for the command
    char    *infile;      // File for input redirection ('<')
    char    *heredoc;     // Heredoc delimiter ('<<')
    char    *outfile;     // File for output redirection ('>')
    int     append;       // 1 if '>>', 0 if '>'
    struct s_simple_cmds *next;
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
void	remove_slash(char **line);
int		get_pwd_len(char **envp, int *i);

/*utils*/
t_shell	copy_env(char **envp);
void    free_env(char **env);
int		check_only_spaces(char *line);
void    print_error(char *error);


/*lexer*/
t_token *lexer(char *str, t_shell *g_env);
void	handle_token(char *str, t_token **head, t_token **current, int *i);
t_token *new_token(t_type type, char *str);
void    fill_token(t_token **head, t_token **current, t_token *new);
void	free_tokens(t_token **head);
int		handle_quotes(char *str, int *i, t_token **current, t_token **head);
void	print_tokens(t_token *head); //delete plus tard
void	move_to_closing_quote(char *str, int *i, char quote_type);
int		get_nbr_quotes(char *str, char quote_type);

/*parser*/
void			print_parser(t_simple_cmds *cmds);
void 			parse_tokens(t_token *tokens);
void			parser2(t_token **tokens, t_shell *g_env);
void			remove_quotes(char **str);
void			expand_dollar(char	**str, t_shell g_env);
char			*ft_strjoin_char_free(char *s, char c);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strreplace(char *str, char *old, char *new);
t_simple_cmds	*tokenize(t_token *tokens);
void 			free_simple_cmds(t_simple_cmds *cmd);

/*execution*/
void execute_command(t_token *token, char **env);
void execute_tokens(t_token *tokens, t_shell *shell);
void handle_pipe(t_token *tokens, char **env);
void handle_redirection(t_token *token);

#endif