/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/24 18:37:17 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_input(t_simple_cmds *cmd)
{
    int fd;
    
    if (cmd->heredoc)
        ;
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
        fprintf(stderr, "Attempting to redirect output to: %s\n", cmd->outfile);
        if (cmd->append)
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
        {
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            
        }
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

int handle_redirection(t_simple_cmds *cmd)
{
    if (redirect_input(cmd) == -1)
        return (-1);
    if (redirect_output(cmd) == -1)
        return (-1);
    return (0);
}

int redirect_input_pipeline(const char *infile)
{
    int fd = open(infile, O_RDONLY);
    if (fd == -1)
    {
        perror("Error: opening input file");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Error: dup2 for input failed");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
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

