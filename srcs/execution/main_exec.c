/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lecartuy <lecartuy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:18:06 by lecartuy          #+#    #+#             */
/*   Updated: 2025/02/19 15:44:34 by lecartuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_tokens(t_token *tokens, t_shell *shell)
{
    while (tokens)
    {
        if (tokens->type == CMD)
            execute_command(tokens->str, shell->env);
        else if (tokens->type == PIPE)
            handle_pipe(tokens, shell->env);
        else if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT || tokens->type == APPEND || tokens->type == HEREDOC)
            handle_redirection(tokens);
        tokens = tokens->next;
    }
}