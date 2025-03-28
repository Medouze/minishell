/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:51:56 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/28 23:47:56 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void process_quotes(char c, char *quote_type, char *new_str, int *j)
{
    // If not in a quote and we hit a quote, start quoting
    if (!(*quote_type) && (c == '\'' || c == '\"'))
    {
        *quote_type = c;
        return; // Don't add the opening quote to output
    }
    
    // If we're in a quote and hit matching quote, end quoting
    else if (*quote_type == c)
    {
        *quote_type = 0;
        return; // Don't add the closing quote to output
    }
    
    // Special handling for double quotes inside double quotes
    else if (*quote_type == '\"' && c == '\"')
    {
        return; // Remove inner double quotes
    }
    
    // Default case - add the character
    new_str[(*j)++] = c;
}

static char *remove_quotes_according_to_rules(const char *str)
{
    char *new_str = malloc(ft_strlen(str) + 1);
    if (!new_str)
        return NULL;
    
    int i = 0;
    int j = 0;
    char quote_type = 0;
    
    while (str[i])
    {
        if (str[i] == '\\' && str[i + 1]) // Handle escaped characters
        {
            new_str[j++] = str[++i];
            i++;
            continue;
        }
        
        if (str[i] == '\'' || str[i] == '\"')
            process_quotes(str[i], &quote_type, new_str, &j);
        else
            new_str[j++] = str[i];
        
        i++;
    }
    new_str[j] = '\0';
    return new_str;
}

void remove_quotes(char **str)
{
    if (!str || !*str)
        return;
    
    // Special case: if fully wrapped in same quote type
    if (((*str)[0] == '\"' && (*str)[ft_strlen(*str) - 1] == '\"') ||
        ((*str)[0] == '\'' && (*str)[ft_strlen(*str) - 1] == '\''))
    {
        char *temp = ft_substr(*str, 1, ft_strlen(*str) - 2);
        free(*str);
        *str = temp;
    }
    else
    {
        char *new_str = remove_quotes_according_to_rules(*str);
        if (new_str) {
            free(*str);
            *str = new_str;
        }
    }
}
