/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:48 by lecartuy          #+#    #+#             */
/*   Updated: 2025/03/08 12:00:07 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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