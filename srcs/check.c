/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:10:04 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/05 15:49:44 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    check_builtin(char **line, char ***envp)
{
    if (ft_strncmp(line[0], "echo", 5) == 0)
        echo(line);
    if (ft_strncmp(line[0], "pwd", 4) == 0)
        pwd(*envp);
    if (ft_strncmp(line[0], "exit", 5) == 0)
        exit_cmd(line, *envp);
    if (ft_strncmp(line[0], "env", 4) == 0)
        env_cmd(*envp);
    if (ft_strncmp(line[0], "export", 7) == 0)
        export_env(line, envp, line[1]);
    if (ft_strncmp(line[0], "unset", 6) == 0)
        unset_env(line, envp, line[1]);
    if (ft_strncmp(line[0], "cd", 3) == 0)
        cd_cmd(line, envp);
    // if (ft_strncmp(line[0], "$?", 3) == 0)
    //     print_error(error);
    // else
    //     lexer(line);
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
