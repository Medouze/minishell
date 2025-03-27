/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:01:45 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 11:15:31 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_simple_cmds(t_simple_cmds *cmd)
{
	t_simple_cmds	*tmp;
	int				i;

	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int	get_nbr_cmd(t_token **tokens)
{
	int	len;

	len = 0;
	while (*tokens && (*tokens)->type == CMD)
	{
		len++;
		*tokens = (*tokens)->next;
	}
	return (len);
}
