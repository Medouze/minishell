/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2024/12/11 16:50:24 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    check_builtin(char **line, char **envp)
{
    if (ft_strncmp(line[0], "echo", 5) == 0)
        echo(line);
    if (ft_strncmp(line[0], "pwd", 4) == 0)
        pwd(envp);
    if (ft_strncmp(line[0], "exit", 5) == 0)
        exit_cmd(line);
    if (ft_strncmp(line[0], "env", 4) == 0)
        env_cmd(envp);
}

// char	*check_cmd(char *cmd, char **envp)
// {
// 	char	**all_paths;
// 	int		i;
// 	char	*full_path;
// 	char	*exec_path;

// 	all_paths = ft_split(get_env("PATH", envp), ':');
// 	if (!all_paths)
// 		return (NULL);
// 	i = 0;
// 	while (all_paths[i])
// 	{
// 		full_path = ft_strjoin(all_paths[i], "/");
// 		exec_path = ft_strjoin(full_path, cmd);
// 		free(full_path);
// 		if (!access(exec_path, F_OK | X_OK))
// 		{
// 			free_path(all_paths);
// 			return (exec_path);
// 		}
// 		free(exec_path);
// 		i++;
// 	}
// 	free_path(all_paths);
// 	return (NULL);
// }
