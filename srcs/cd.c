/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/01/31 16:13:14 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void remove_slash(char **line)
{
    char *new_line;
    size_t len;

    if (line == NULL || *line == NULL)
        return;
    len = ft_strlen(*line);
    if (len > 0 && (*line)[len - 1] == '/')
        len--;
    new_line = malloc(sizeof(char) * (len + 1));
    if (!new_line)
        return;
    ft_strlcpy(new_line, *line, len + 1);
    free(*line);
    *line = new_line;
}

char    *get_pwd(char **envp)
{
    int     i;
    char    *pwd;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD=", 4) == 0)
        {
            pwd = ft_strdup(envp[i] + 4);
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
    int     pwd_len;
    int     i;
    int     j;
    char    *new_pwd;

    i = 0;
    pwd_len = 0;
    while ((*envp)[i])
    {
        if (ft_strlen((*envp)[i]) == 5)
            return ;
        if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
        {
            pwd_len = ft_strlen((*envp)[i]) - ft_strlen(ft_strrchr((*envp)[i], '/'));
            break ;
        }
        i++;
    }
    new_pwd = malloc(sizeof(char) * (pwd_len + 1));
    j = 0;
    while (j < pwd_len)
    {
        new_pwd[j] = (*envp)[i][j];
        j++;
    }
    new_pwd[j] = '\0';
    if (ft_strlen(new_pwd) == 4)
    {
        free(new_pwd);
        new_pwd = ft_strdup("PWD=/");
    }
    free((*envp)[i]);
    (*envp)[i] = ft_strdup(new_pwd);
    free(new_pwd);
    change_old_pwd(envp, old_pwd);
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
    new_old_pwd = get_pwd(*envp);
    if (new_path[0] != '\0')
        addto_pwd(envp, new_path, new_old_pwd);
    change_old_pwd(envp, old_pwd);
    free(new_old_pwd);
    free(new_path);
}

void    cd_cmd(char **line, char ***envp)
{
    char    *home;
    char    *old_pwd;
    char    *pwd;

    home = getenv("HOME");
    old_pwd = get_pwd(*envp);
    if (!line[1] || (line[1] && line[1][0] == '~') || (line[1] && !ft_strncmp(line[1], "~/", 2)))
    {
        if (chdir(home) == -1)
            return ;
        change_pwd(envp, home);
        free(old_pwd);
        return ;
    }
    if (line[1] && ft_strncmp(line[1], ".", 5) != 0)
    {
        if (line[1][0] == '/')
            change_pwd(envp, line[1]);
        else if (ft_strncmp(line[1], "..", 2) == 0)
        {
            if (ft_strncmp(line[1], "..", 3) == 0)
                back_pwd(envp, old_pwd);
            if (ft_strncmp(line[1], "../", 3) == 0)
            {
                if (line[1][ft_strlen(line[1]) - 1] == '/' && line[1][ft_strlen(line[1]) - 2] != '.')
                    remove_slash(&line[1]);
                back_absolute_pwd(envp, line[1], old_pwd);
            }
        }
        else
        {
            if (line[1][ft_strlen(line[1]) - 1] == '/' && ft_strncmp(line[1], "../", 3))
                remove_slash(&line[1]);
            addto_pwd(envp, line[1], old_pwd);
        }
        if (chdir(pwd = get_pwd(*envp)) == -1)
        {
            // if (ft_strncmp(pwd, "PWD=/", 5))
            // {
            //     free(pwd);
            //     free(old_pwd);
            //     return;
            // }
            printf("minishell: cd: %s: No such file or directory\n", line[1]);
            change_pwd(envp, old_pwd);
            free(pwd);
            free(old_pwd);
            return ;  
        }
        free(pwd);
    }
    free(old_pwd);
}
