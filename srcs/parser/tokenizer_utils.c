/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:01:45 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/10 16:02:07 by mlavergn         ###   ########.fr       */
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

void	print_simple_cmds(t_simple_cmds *cmd) // DELETE PLUS TARD
{
	int	i;

	while (cmd)
	{
		printf("Command: ");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("%s ", cmd->args[i]);
				i++;
			}
		}
		printf("\n");
		if (cmd->infile)
			printf("Input Redirection: %s\n", cmd->infile);
		if (cmd->heredoc)
			printf("Heredoc: %s\n", cmd->heredoc);
		if (cmd->outfile)
		{
			printf("Output Redirection: %s", cmd->outfile);
			if (cmd->append)
				printf(" (append)");
			printf("\n");
		}
		cmd = cmd->next;
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
