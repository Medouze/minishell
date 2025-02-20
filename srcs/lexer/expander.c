/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:37 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/20 21:27:28 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_env_value(const char *var)
{
    if (strcmp(var, "USER") == 0)
        return ft_strdup("hello");
    return NULL;
}

void expand_dollar(char *str)
{
    int i = 0, j = 0;
    int length = strlen(str);
    char *new_str = malloc(length + 1);
    if (!new_str)
        return;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] != '\0')
        {
            int start = i + 1;
            int finish = start;
            while (str[finish] && str[finish] != ' ' && str[finish] != '"' && str[finish] != '\'')
                finish++;
            char *var_name = strndup(&str[start], finish - start);
            if (var_name)
            {
                char *var_value = get_env_value(var_name);
                if (var_value)
                {
                    for (int k = 0; var_value[k] != '\0'; k++)
                    {
                        new_str[j++] = var_value[k];
                    }
                }
                free(var_name);
            }
            i = finish;
        }
        else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    strcpy(str, new_str);
    free(new_str);
}

void    handle_quotes_2(t_token *tokens, char **str)
{
    if (!check_closed(*str, '\'') || !check_closed(*str, '\"'))
	{
        printf("tttt\n");
		free_tokens(tokens);
		print_error("Unclosed quotes\n");
	}
}

void    expander(t_token **tokens, t_shell g_env)
{
    (void)g_env;
    t_token *current;
    //char    *new_str;

    current = *tokens;
    while (current)
    {
        if (ft_strchr(current->str, '\'') || ft_strchr(current->str, '\"'))
        {
            handle_quotes_2(*tokens, &current->str);
        }
        current = current->next;
    }
}
