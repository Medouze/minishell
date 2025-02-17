/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/17 22:47:32 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

structure de mon parser 

t_simple_cmds *parse_simple_cmd(t_token **tokens)
{
    t_simple_cmds *cmd = malloc(sizeof(t_simple_cmds));
    cmd->str = malloc(sizeof(char *) * (num_tokens + 1)); // Track the number of tokens
    cmd->num_redirections = 0;
    cmd->hd_file_name = NULL;
    cmd->redirections = NULL;

    int i = 0;

    // Find the command (CMD type)
    if (*tokens && (*tokens)->type == CMD)
    {
        cmd->str[i++] = (*tokens)->str;
        *tokens = (*tokens)->next;  // Move to the next token
    }

    // Process any redirections (if any)
    while (*tokens && ((*tokens)->type == REDIRECT_IN || (*tokens)->type == REDIRECT_OUT || (*tokens)->type == APPEND))
    {
        // Handle the redirection here (store in cmd)
        // Example: Store redirection and filename
        if ((*tokens)->type == REDIRECT_IN)
        {
            // process REDIRECT_IN
        }
        else if ((*tokens)->type == REDIRECT_OUT)
        {
            // process REDIRECT_OUT
        }
        else if ((*tokens)->type == APPEND)
        {
            // process APPEND
        }

        cmd->num_redirections++;
        *tokens = (*tokens)->next;  // Move to the next token
    }

    // Check if there is a pipe
    if (*tokens && (*tokens)->type == PIPE)
    {
        // Create the current command
        cmd->str[i] = NULL;  // Mark the end of arguments for this command
        *tokens = (*tokens)->next;  // Move past the pipe

        // Parse the next command (after the pipe)
        t_simple_cmds *next_cmd = parse_simple_cmd(tokens);  // Recursively parse the next command

        // Link the commands together (i.e., the pipe connects them)
        cmd->next = next_cmd;
    }

    // After processing, mark the end of the current command arguments list
    cmd->str[i] = NULL;

    return cmd;
}