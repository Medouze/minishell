/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/28 22:52:25 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int read_heredoc_input(int fd, t_simple_cmds *cmd, t_shell *shell)
{
    t_heredoc *current;
    char *line;

    current = cmd->heredocs;
    while (current)
    {
        printf("%s\n",current->delimiter);
        while (1)
        {
            line = readline("> ");
            if (!line || ft_strncmp(line, current->delimiter, ft_strlen(current->delimiter) + 1) == 0)
                break;
            expand_dollar(&line, *shell);
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        printf("test\n");
        free(line);
        current = current->next;
    }
    close(fd);
    return (0);
}

static int handle_heredoc(t_simple_cmds *cmd, t_shell *shell)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
        return (perror("pipe"), -1);
    if (read_heredoc_input(pipe_fd[1], cmd, shell) == -1)
        return (-1);
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 for heredoc failed");
        close(pipe_fd[0]);
        return (-1);
    }
    close(pipe_fd[0]);
    return (0);
}

int redirect_input(t_simple_cmds *cmd, t_shell *shell)
{
    int fd;

    if (cmd->heredocs)
    {
        if (handle_heredoc(cmd, shell) == -1)
            return (-1);
    }
    else if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening input file");
            return (-1);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 for input failed");
            close(fd);
            return (-1);
        }
        close(fd);
    }
    return (0);
}

int redirect_output(t_simple_cmds *cmd)
{
    int fd;
    t_outfile *out = cmd->outfiles;

    while (out)
    {
        if (out->append)
            fd = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("Failed to open output file");
            return (-1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 for output failed");
            close(fd);
            return (-1);
        }
        close(fd);
        out = out->next;
    }
    return (0);
}

int handle_redirection(t_simple_cmds *cmd, t_shell *shell)
{
    if (redirect_input(cmd, shell) == -1)
        return (-1);
    if (redirect_output(cmd) == -1)
        return (-1);
    return (0);
}


