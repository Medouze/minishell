/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:10:46 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 17:04:17 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

# ifndef SPE_CHARS
#  define SPE_CHARS "!#$%&()*+,-./:;<=>?@[\\]^_`{|}~"
# endif

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
	char	**hidden_env;
	int		last_exit;
}	t_shell;

typedef struct s_arg_node
{
	char				*arg;
	struct s_arg_node	*next;
}	t_arg_node;

typedef struct s_simple_cmds
{
	char					**args;
	char					*infile;
	char					*heredoc;
	char					*outfile;
	int						append;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

/*checks*/
int				check_builtin(char **line, char ***envp, int *last_exit);
char			*check_cmd(char *cmd, char **envp);

/*built in*/
void			echo(char **line);
void			pwd(char **envp);
void			exit_cmd(char **line, char **envp);
void			env_cmd(char **myenv, int export);
void			export_env(char **line, char ***envp, char *export);
void			unset_env(char **line, char ***envp, char *unset);
void			cd_cmd(char **line, char ***envp);
void			remove_slash(char **line);
int				get_pwd_len(char **envp, int *i);
char			*extract_key(char *line);
int				replace_line(char ***envp, char *line);
char			*get_var(char **envp, char *line);
void			addto_pwd(char ***envp, char *path, char *old_pwd);
void			remove_slash(char **line);
void			change_old_pwd(char ***envp, char *old_pwd);
void			change_pwd(char ***envp, char *path);
void			back_pwd(char ***envp, char *old_pwd);
void			back_absolute_pwd(char ***envp, char *path, char *old_pwd);

/*utils*/
t_shell			copy_env(char **envp);
void			free_env(char **env);
int				check_only_spaces(char *line);
void			print_error(char *error);

/*lexer*/
t_token			*lexer(char *str, t_shell *g_env);
void			handle_token(char *str,
					t_token **head, t_token **current, int *i);
t_token			*new_token(t_type type, char *str);
void			fill_token(t_token **head, t_token **current, t_token *new);
void			free_tokens(t_token **head);
int				handle_quotes(char *str, int *i,
					t_token **current, t_token **head);
void			print_tokens(t_token *head); //delete plus tard
void			move_to_closing_quote(char *str, int *i, char quote_type);
int				get_nbr_quotes(char *str, char quote_type);

/*parser*/
t_simple_cmds	*parser2(t_token **tokens, t_shell *g_env);
void			remove_quotes(char **str);
void			expand_dollar(char	**str, t_shell g_env);
char			*ft_strjoin_char_free(char *s, char c);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strreplace(char *str, char *old, char *new);
t_simple_cmds	*tokenize(t_token *tokens);
void			free_simple_cmds(t_simple_cmds *cmd);
int				get_nbr_cmd(t_token **tokens);
void			expand_tilde(char **path, t_shell g_env);
int				inside_quotes(char	*str);
void			in_quotes(char **str, int i, int *in_double, int *in_single);

/*execution*/
int				redirect_input_pipeline(const char *infile);
int				redirect_output_pipeline(const char *outfile, int append);
int				redirect_input(t_simple_cmds *cmd, t_shell *shell);
int				redirect_output(t_simple_cmds *cmd);
void			handle_pipe(t_simple_cmds *cmds, t_shell *shell);
void			execute_tokens(t_simple_cmds *cmds, t_shell *shell);
void			execute_command(t_simple_cmds *cmd, t_shell *shell);
int				handle_redirection(t_simple_cmds *cmd, t_shell *shell);
void			execute_command_pipe(t_simple_cmds *cmd, t_shell *shell);

/*signals*/

void			ft_sig_handling(int sig);
void			ft_sig_heredoc(int sig);
void			ft_handler_signal(int pick);
void			handle_sigquit(int sig);

#endif