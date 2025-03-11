/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:49 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/11 17:04:49 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_slash(char **line)
{
    size_t len;

    if (line == NULL || *line == NULL)
        return;

    len = ft_strlen(*line);
    if (len > 0 && (*line)[len - 1] == '/')
    {
        (*line)[len - 1] = '\0';  // Replace the last '/' with null terminator
    }
}

char    *get_var(char **envp, char *line)
{
    int     i;
    char    *pwd;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], line, ft_strlen(line)) == 0)
        {
            pwd = ft_strdup(envp[i] + ft_strlen(line) + 1);
            return (pwd);
        }
        i++;
    }
    printf("Couldnt find PATH\n");
    return (NULL);
}

void    change_old_pwd(char ***envp, char *old_pwd)
{
    int i;

    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], "OLDPWD=", 6) == 0)
        {
            free((*envp)[i]);
            (*envp)[i] = ft_strjoin("OLDPWD=", old_pwd);
            return ;
        }
        i++;
    }
}

void    addto_pwd(char ***envp, char *path, char *old_pwd)
{
    int     i;
    char    *new_path;
    char    *final_path;

    i = 0;
    final_path = NULL;
    final_path = ft_strjoin("/", path);
    new_path = ft_strjoin(old_pwd, final_path);
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
        {
            free((*envp)[i]);
            if (new_path[0] == '/' && new_path[1] == '/')
                (*envp)[i] = ft_strjoin("PWD=", new_path + 1);
            else
                (*envp)[i] = ft_strjoin("PWD=", new_path);
            free(new_path);
            free(final_path);
            change_old_pwd(envp, old_pwd);
            return ;
        }
        i++;
    }
}

void    change_pwd(char ***envp, char *path)
{
    int i;

    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
        {
            free((*envp)[i]);
            (*envp)[i] = ft_strjoin("PWD=", path);
            return ;
        }
        i++;
    }
}

void    back_pwd(char ***envp, char *old_pwd)
{
    char *pwd = get_var(*envp, "PWD");
    char *new_pwd;
    char *last_slash = ft_strrchr(pwd, '/');

    if (!pwd || ft_strlen(pwd) == 1) // Root case
    {
        free(pwd);
        return ;
    }
    new_pwd = ft_substr(pwd, 0, last_slash - pwd); // Trim last dir
    free(pwd);

    change_pwd(envp, new_pwd);
    change_old_pwd(envp, old_pwd);
    free(new_pwd);
}

void    back_absolute_pwd(char ***envp, char *path, char *old_pwd)
{   
    char    *new_path;
    char    *tmp;
    char    *new_old_pwd;

    new_path = ft_strdup(path);
    while (1)
    {
        if (ft_strncmp(new_path, "../", 3) == 0)
        {
            back_pwd(envp, old_pwd);
            tmp = new_path;
            new_path = ft_strdup(new_path + 3);
            free(tmp);
        }
        else
            break ;
    }
    new_old_pwd = get_var(*envp, "PWD");
    if (new_path[0] != '\0')
        addto_pwd(envp, new_path, new_old_pwd);
    change_old_pwd(envp, old_pwd);
    free(new_old_pwd);
    free(new_path);
}

void cd_cmd(char **line, char ***envp)
{
    char *current_pwd;
    char *path;
    char *previous_pwd;

    current_pwd = get_var(*envp, "PWD");  // Dynamically allocated
    if (line[1])
        path = ft_strdup(line[1]);  // Always strdup line[1]
    else
        path = get_var(*envp, "HOME");  // Dynamically allocated
    if (!path || ft_strncmp(path, "", 1) == 0)
    {
        if (!path)
            printf("minishell: cd: HOME not set\n");
        free(current_pwd);
        free(path);  // Free path if it was allocated
        return;
    }
    if (ft_strncmp(path, "-", 1) == 0)
    {
        previous_pwd = get_var(*envp, "OLDPWD");  // Dynamically allocated
        if (!previous_pwd)
        {
            printf("minishell: cd: OLDPWD not set\n");
            free(current_pwd);
            free(path);  // Free path
            return;
        }
        if (chdir(previous_pwd) == -1)
        {
            printf("minishell: cd: %s: No such file or directory\n", previous_pwd);
            free(current_pwd);
            free(previous_pwd);
            free(path);  // Free path
            return;
        }
        change_pwd(envp, previous_pwd);
        free(current_pwd);
        free(previous_pwd);
        free(path);  // Free path
        return;
    }
    if (line[1] != NULL)
        remove_slash(&path);  // Remove trailing slash from the duplicated path
    if (chdir(path) == -1)
    {
        printf("minishell: cd: %s: No such file or directory\n", path);
        free(current_pwd);
        free(path);  // Free path
        return;
    }
    if (strncmp(path, ".", 1) == 0)
    {
        if (ft_strncmp(path, "..", 2) == 0)
        {
            if (ft_strncmp(path, "../", 3) == 0)
                back_absolute_pwd(envp, path, current_pwd);
            else
                back_pwd(envp, current_pwd);
        }
        else
        {
            free(current_pwd);
            free(path);  // Free path
            return; 
        }
    }
    else if (path[0] == '/')
        change_pwd(envp, path);
    else
        addto_pwd(envp, path, current_pwd);
    free(current_pwd);
    free(path);  // Free path
}
