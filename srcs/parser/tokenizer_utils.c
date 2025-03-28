/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:01:45 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/28 16:35:37 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_simple_cmds(t_simple_cmds *cmd)
{
	t_outfile		*tmp;
	t_simple_cmds	*temp;
	int				i;

	while (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		while (cmd->outfiles)
		{
			tmp = cmd->outfiles;
			cmd->outfiles = cmd->outfiles->next;
			free(tmp->filename);
			free(tmp);
		}
		temp = cmd;
		cmd = cmd->next;
		free(temp);
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

void	add_outfile(t_outfile **outfiles, char *filename, int append)
{
	t_outfile	*new;
	t_outfile	*tmp;

	new = malloc(sizeof(t_outfile));
	if (!new)
		return ;
	new->filename = ft_strdup(filename);
	new->append = append;
	new->next = NULL;
	if (!*outfiles)
		*outfiles = new;
	else
	{
		tmp = *outfiles;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
