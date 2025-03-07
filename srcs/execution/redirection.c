/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/07 13:36:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void handle_file_redirection(t_token *token)
{
    int fd;

    fd = 0;
    if (token->type == REDIRECT_IN) // <
    {
        fd = open(token->next->str, O_RDONLY);
        if (fd == -1)
            print_error("Error: Cannot open input file");
        dup2(fd, STDIN_FILENO);
    }
    else if (token->type == REDIRECT_OUT) // >
    {
        fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            print_error("Error: Cannot open output file");
        dup2(fd, STDOUT_FILENO);
    }
    else if (token->type == APPEND) // >>
    {
        fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            print_error("Error: Cannot open output file");
        dup2(fd, STDOUT_FILENO);
    }
    close(fd);
}

static void handle_heredoc(char *delimiter)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
        print_error("Error: Pipe creation failed");
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
            break;
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}

void handle_redirection(t_token *token)
{
    if (token->type == HEREDOC)
        handle_heredoc(token->next->str);
    else
        handle_file_redirection(token);
}