/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/26 20:36:34 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int handle_heredoc(t_simple_cmds *cmd)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strncmp(line, cmd->heredoc, ft_strlen(cmd->heredoc) + 1) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]); 
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 for heredoc failed");
        close(pipe_fd[0]);
        return (-1);
    }
    close(pipe_fd[0]);
    return (0);
}

int redirect_input(t_simple_cmds *cmd)
{
    int fd;

    if (cmd->heredoc)
    {
        if (handle_heredoc(cmd) == -1)
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

    if (cmd->outfile)
    {
        if (cmd->append)
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd == -1)
        {
            perror("[ERROR] Failed to open output file");
            return (-1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("[ERROR] dup2 for output failed");
            close(fd);
            return (-1);
        }
        //close(fd);
    }
    return (0);
}

int redirect_input_pipeline(const char *infile)
{
    int fd;
    
    fd = open(infile, O_RDONLY);
    if (fd == -1)
    {
        perror("Error: opening input file");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Error: dup2 for input failed");
        close(fd);
        return -1;
    }
    close(fd);
    return (0);
}

int redirect_output_pipeline(const char *outfile, int append)
{
    int fd;

    if (append)
        fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    if (fd == -1)
    {
        perror("Error: opening output file");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Error: dup2 for output failed");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

