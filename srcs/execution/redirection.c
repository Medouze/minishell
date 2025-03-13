/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/13 16:47:48 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_input(t_simple_cmds *cmd)
{
    int fd;

    if (cmd->heredoc)
    {
        fd = open(cmd->heredoc, O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening heredoc");
            return (-1);
        }
        printf("Redirecting input from heredoc: %s (fd = %d)\n", cmd->heredoc, fd);
        if (dup2(fd, STDIN_FILENO) == -1)
            perror("dup2 for input failed");
        close(fd);
    }
    else if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening input file");
            return (-1);
        }
        printf("Redirecting input from: %s (fd = %d)\n", cmd->infile, fd);
        if (dup2(fd, STDIN_FILENO) == -1)
            perror("dup2 for input failed");
        close(fd);
    }
    return (0);
}

int redirect_output(t_simple_cmds *cmd)
{
    int fd;

    if (cmd->outfile)
    {
        if (cmd->append)
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("Error opening output file");
            return (-1);
        }
        printf("Redirecting output to: %s (fd = %d)\n", cmd->outfile, fd);
        if (dup2(fd, STDOUT_FILENO) == -1)
            perror("dup2 for output failed");
        close(fd);
    }
    return (0);
}


void redirect_input_pipeline(const char *infile)
{
    int fd = open(infile, O_RDONLY);
    if (fd == -1)
    {
        perror("Error: opening input file");
        _exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void redirect_output_pipeline(const char *outfile, int append)
{
    int fd;

    if (append)
        fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error: opening output file");
        _exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}
