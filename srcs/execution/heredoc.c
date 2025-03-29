/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:54:10 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/28 23:59:24 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_line_and_expand(char **line, t_shell *shell)
{
	*line = readline("> ");
	if (!*line)
		return (0);
	expand_dollar(line, *shell);
	return (1);
}

void	write_line_to_fd(int fd, char *line, char *delimiter, char *last_delim)
{
	if (!ft_strncmp(delimiter, last_delim, ft_strlen(delimiter) + 1))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

int	read_heredoc_input(int fd, t_simple_cmds *cmd, t_shell *shell)
{
	t_heredoc	*current;
	char		*line;
	char		*last_delim;

	current = cmd->heredocs;
	last_delim = find_last_heredoc(cmd->heredocs);
	while (current)
	{
		if (!read_line_and_expand(&line, shell))
			break ;
		while (ft_strncmp(line, current->delimiter,
				ft_strlen(current->delimiter) + 1) != 0)
		{
			write_line_to_fd(fd, line, current->delimiter, last_delim);
			free(line);
			if (!read_line_and_expand(&line, shell))
				break ;
		}
		free(line);
		current = current->next;
	}
	close(fd);
	return (0);
}
