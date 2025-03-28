/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:01:45 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/28 22:59:13 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_simple_cmds(t_simple_cmds *cmd)
{
	t_outfile		*tmp;
	t_heredoc		*tmph;
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
		while (cmd->heredocs)
		{
			tmph = cmd->heredocs;
			cmd->heredocs = cmd->heredocs->next;
			free(tmph);
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

void add_heredoc(t_heredoc **heredocs, char *delimiter)
{
    t_heredoc *new_heredoc = malloc(sizeof(t_heredoc));
    if (!new_heredoc)
        return;

    new_heredoc->delimiter = delimiter;
    new_heredoc->next = NULL;

    // If the heredocs list is empty, make the new heredoc the first element
    if (*heredocs == NULL)
    {
        *heredocs = new_heredoc;
    }
    else
    {
        // Otherwise, find the last node and add the new heredoc to the end
        t_heredoc *current = *heredocs;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_heredoc;
    }
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


