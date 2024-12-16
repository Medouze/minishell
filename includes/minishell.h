/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:57:07 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/16 16:23:23 by mlavergn         ###   ########.fr       */
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

#endif