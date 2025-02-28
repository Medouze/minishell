/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:25:46 by lecartuy          #+#    #+#             */
/*   Updated: 2025/02/27 22:04:18 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void execute_child(t_token *cmd, int pipe_fd[][2], int index, int num_pipes, char **env)
{
    int i;
    
    i = 0;
    if (index > 0)
        dup2(pipe_fd[index - 1][0], STDIN_FILENO);
    if (index < num_pipes)
        dup2(pipe_fd[index][1], STDOUT_FILENO);
    while (i < num_pipes)
    {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
        i++;
    }
    execute_command(cmd, env);
}

static void execute_pipeline(t_token *tokens, int pipe_fd[][2], int num_pipes, char **env)
{
    int i;
    pid_t pid;
    t_token *current;
    
    i = 0;
    current = tokens;
    while (current)
    {
        if (current->type == CMD)
        {
            pid = fork();
            if (pid == 0)
            {
                execute_child(current, pipe_fd, i, num_pipes, env);
                exit(1);
            }
            i++;
        }
        current = current->next;
    }
}

static int count_pipes(t_token *tokens)
{
    int count;
    
    count = 0;
    while (tokens)
    {
        if (tokens->type == PIPE)
            count++;
        tokens = tokens->next;
    }
    return (count);
}

void handle_pipe(t_token *tokens, char **env)
{
    int num_pipes;
    int i;
    num_pipes = count_pipes(tokens);
    int pipe_fd[num_pipes][2];
    
    i = 0;
    while (i < num_pipes)
    {
        if (pipe(pipe_fd[i]) == -1)
            print_error("Error: Pipe creation failed");
        i++;
    }
    execute_pipeline(tokens, pipe_fd, num_pipes, env);

    i = 0;
    while (i < num_pipes)
    {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
        i++;
    }

    while (wait(NULL) > 0);
}
