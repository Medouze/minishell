/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:10:46 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/03 16:51:04 by lecartuy         ###   ########.fr       */
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
# include <errno.h>

# ifndef SPE_CHARS
#  define SPE_CHARS "!#$%&()*+,-./:;=?@[\\]^_`{|}~"
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

typedef struct s_heredoc
{
	char				*delimiter;
	struct s_heredoc	*next;
}	t_heredoc;

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

typedef struct s_outfile
{
	char				*filename;
	int					append;
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_pipe_data
{
	int	(*pipe_fd)[2];
	int	index;
	int	num_pipes;
}	t_pipe_data;

typedef struct s_simple_cmds
{
	char					**args;
	char					*infile;
	t_heredoc				*heredocs;
	t_outfile				*outfiles;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

/*checks*/
int				check_builtin(char **line, char ***envp, int *last_exit);

/*built in*/
void			echo(char **line);
void			pwd(char **envp);
void			exit_cmd(char **line, char **envp, int *last_exit);
void			env_cmd(char **myenv, int export);
void			export_env(char **line, char ***envp,
					char *export, int *last_exit);
void			unset_env(char **line, char ***envp,
					char *unset, int *last_exit);
int				cd_cmd(char **line, char ***envp);
void			remove_slash(char **line);
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
void			copy_quoted_content(char *buffer,
					int *buf_index, char *str, int *i);
int				check_closed_dollar(char **str, t_token **head, t_shell g_env);
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
int				check_closed(char *str);
int				closed(char *str);

/*parser*/
void			add_heredoc(t_heredoc **heredocs, char *delimiter);
void			add_outfile(t_outfile **outfiles, char *filename, int append);
t_simple_cmds	*parser2(t_token **tokens, t_shell *g_env);
void			remove_quotes(char **str);
void			expand_dollar(char	**str, t_shell g_env);
char			*ft_strjoin_char_free(char *s, char c);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strreplace(char *str, char *old, char *new);
t_simple_cmds	*tokenize(t_token *tokens);
void			free_simple_cmds(t_simple_cmds *cmd);
int				get_nbr_cmd(t_token *tokens);
void			expand_tilde(char **path, t_shell g_env);
int				inside_quotes(char	*str);
void			in_quotes(char **str, int i, int *in_double, int *in_single);

/*execution*/
int				read_heredoc_input(int fd, t_simple_cmds *cmd, t_shell *shell);
char			*find_last_heredoc(t_heredoc *heredocs);
int				redirect_input(t_simple_cmds *cmd, t_shell *shell);
int				redirect_output(t_simple_cmds *cmd);
void			handle_pipe(t_simple_cmds *cmds, t_shell *shell);
void			execute_tokens(t_simple_cmds *cmds, t_shell *shell);
void			execute_command(t_simple_cmds *cmd, t_shell *shell);
int				handle_redirection(t_simple_cmds *cmd, t_shell *shell);
void			execute_command_pipe(t_simple_cmds *cmd, t_shell *shell);
void			free_tab(char **tab);
void			wait_for_children(t_shell *shell);
void			handle_exec_exit(pid_t pid, t_shell *shell);
void			execute_command_pipe(t_simple_cmds *cmd, t_shell *shell);
char			**get_paths(char **env);
char			*find_exec(char *cmd, char **paths);
int				handle_heredoc(t_simple_cmds *cmd, t_shell *shell);
/*signals*/

void			ft_sig_handling(int sig);
void			ft_sig_heredoc(int sig);
void			ft_handler_signal(int pick);
void			ft_sigint_received(int sigint_received);

#endif