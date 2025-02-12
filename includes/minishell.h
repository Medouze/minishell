/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:57:07 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/12 17:35:19 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

//extern int	error;

typedef	enum	e_type
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
char    **copy_env(char **envp);
void    free_env(char **env);
void	print_error(int error);

/*lexer*/
t_token *lexer(char *str);
void	handle_token(char *str, t_token **head, t_token **current, int *i);
t_token *new_token(t_type type, char *str);
void    fill_token(t_token **head, t_token **current, t_token *new);
void	free_tokens(t_token *head);

#endif