/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:41:03 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/07 16:56:35 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// Free memory allocated by ft_split
void ft_free_split(char **arr) 
{
    int i = 0;
    if (arr)
    {
        while (arr[i])
        {
            if (arr[i])
                free(arr[i++]);
        }
        free(arr);
    }
}

// Get the current PWD from envp
char *get_pwd(char **envp) 
{
    int i = 0;
    while (envp[i]) 
    {
        if (strncmp(envp[i], "PWD=", 4) == 0)
            return ft_strdup(envp[i] + 4);
        i++;
    }
    return ft_strdup("/");
}

// Update environment variables (PWD, OLDPWD)
void update_env(char ***envp, char *key, char *value) 
{
    int i = 0;
    char *new_entry = ft_strjoin(key, value);
    while ((*envp)[i]) 
    {
        if (strncmp((*envp)[i], key, strlen(key)) == 0) 
        {
            free((*envp)[i]);
            (*envp)[i] = new_entry;
            return;
        }
        i++;
    }
}

char **allocate_and_copy_array(char **src, int size) {
    char **new_array = malloc((size + 1) * sizeof(char *));
    if (!new_array) return NULL;
    
    for (int i = 0; i < size; i++) {
        new_array[i] = ft_strdup(src[i]);
    }
    new_array[size] = NULL;
    return new_array;
}

// Function to process a path part and adjust the array
void process_path_part(char **new_cwd_parts, int *k, char *part) {
    if (ft_strncmp(part, "..", 3) == 0) {
        if (*k > 0) free(new_cwd_parts[--(*k)]);  // Go up one level
    } else if (ft_strncmp(part, ".", 2) != 0 && part[0] != '\0') {
        new_cwd_parts[(*k)++] = ft_strdup(part); // Add directory
    }
}

// Function to build the resolved path string
char *build_resolved_path(char **new_cwd_parts, int k) {
    char *resolved = ft_strdup("/");
    for (int i = 0; i < k; i++) {
        char *tmp = resolved;
        resolved = ft_strjoin(resolved, new_cwd_parts[i]);
        free(tmp);
        if (i < k - 1) {
            tmp = resolved;
            resolved = ft_strjoin(resolved, "/");
            free(tmp);
        }
    }
    return resolved;
}

// Main resolve_path function
char *resolve_path(char *cwd, char *input) {
    printf("Resolving path: cwd = '%s', input = '%s'\n", cwd, input);

    char **parts = ft_split(input, '/');
    char **cwd_parts = ft_split(cwd, '/');

    if (!parts || !cwd_parts) {
        printf("ft_split() failed!\n");
        ft_free_split(parts);
        ft_free_split(cwd_parts);
        return NULL;
    }

    int j = 0;
    while (cwd_parts[j]) j++; // Count depth

    // Allocate a new array for resolved path
    char **new_cwd_parts = allocate_and_copy_array(cwd_parts, j);
    if (!new_cwd_parts) return NULL;

    // Process each part of the path
    int k = j;
    for (int i = 0; parts[i]; i++) {
        process_path_part(new_cwd_parts, &k, parts[i]);
    }
    
    char *resolved = build_resolved_path(new_cwd_parts, k);
    printf("RESOLVED");

    ft_free_split(parts);
    ft_free_split(cwd_parts);
    ft_free_split(new_cwd_parts);

    return resolved;
}


// Main cd command implementation
void cd_cmd(char **args, char ***envp) {
    char *old_pwd = get_pwd(*envp);
    char *target;

    // If no argument is passed, use HOME from the environment
    if (args[1] == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
            printf("minishell: cd: HOME not set\n");
            free(old_pwd);
            return;
        }
    } else {
        target = args[1];
    }

    // Resolve path if not the home directory
    if (ft_strncmp(target, "/", 1) != 0 && ft_strncmp(target, "~", 1) != 0) {
        char *resolved_path = resolve_path(old_pwd, target);
        if (!resolved_path || chdir(resolved_path) == -1) {
            printf("minishell: cd: %s: No such file or directory\n", target);
            free(resolved_path);
            free(old_pwd);
            return;
        }
        free(resolved_path);
    } else if (chdir(target) == -1) {  // For absolute or home directory path
        printf("minishell: cd: %s: No such file or directory\n", target);
        free(old_pwd);
        return;
    }

    // Update PWD and OLDPWD
    update_env(envp, "PWD=", target);
    update_env(envp, "OLDPWD=", old_pwd);

    free(old_pwd);
}



