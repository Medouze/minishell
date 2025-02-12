/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:59:17 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/12 16:03:21 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *new_token(t_type type, char *str)
{
    t_token *new;
    
    new = malloc(sizeof(t_token));
    if (!new)
        return(NULL);
    new->str = ft_strdup(str);
    new->type = type;
    new->next = NULL;

    return(new);
}

void    fill_token(t_token **head, t_token **current, t_token *new, int *i)
{
    if (*head == NULL)
        *head = new;
    else
        (*current)->next = new;
    *current = new;
    (*i)++;
}

char    *copy_str(char *str, int start, int end)
{
    char    *word;
    int     i;
    int length;

    length = end - start;
    word = malloc(sizeof(char) * (length + 1));
    i = 0;
    while (start < end)
    {
        word[i] = str[start];
        i++;
        start++;    
    }
    word[i] = '\0';
    return(word);
}

void print_tokens(t_token *head) // A supprimer par la suite(test)
{
    t_token *current = head;

    while (current)
    {
        printf("Token type: %d, Token value: '%s'\n", current->type, current->str);
        current = current->next;
    }
}


t_token	*lexer(char *str)
{
	t_token	*head;
	t_token	*current;
    t_token *new;
    char    *cmd_str;
    int length;
    int start;
    int i;

    head = NULL;
    current = NULL;
	i = 0;
    while (str[i])
    {
        if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        {
            i++;
            continue;
        }
        else if ((str[i]) == '|')
        {
            new = new_token(PIPE, "|");
            fill_token(&head, &current, new, &i);            
        }
        else if ((str[i]) == '<')
        {
            if (str[i + 1] && str[i + 1] == '<')
            {
                new = new_token (HEREDOC, "<<");
                fill_token(&head, &current, new, &i);
                i++;
            }
            else
            {
                new = new_token(REDIRECT_IN, "<");
                fill_token(&head, &current, new, &i);
            }       
        }
        else if ((str[i]) == '>')
        {
            if (str[i + 1] && str[i + 1] == '>')
            {
                new = new_token (APPEND, ">>");
                fill_token(&head, &current, new, &i);
                i++;
            }
            else
            {
                new = new_token(REDIRECT_OUT, ">");
                fill_token(&head, &current, new, &i);
            }  
        }
        else
        {
            start = i;
            while (ft_isalpha(str[i]))
                i++;
            length = i - start;
            cmd_str = copy_str(str, start, i);
            new = new_token(CMD, cmd_str);
            free(cmd_str);
            fill_token(&head, &current, new, &i);
        }
    }
    //print_tokens(head) Fonction pour voir les tokens;
    return(head);
}

