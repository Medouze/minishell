/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:59:17 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/07 18:05:29 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_word(char *str, int *index)
{
    int size = 0;
    int i = *index;  // Commencer au point où le mot commence
    char *word;

    // Trouver la taille du mot
    while (str[i] && ft_isalpha(str[i])) {
        size++;
        i++;
    }

    // Allouer de la mémoire pour le mot + caractère nul de fin
    word = malloc(sizeof(char) * (size + 1));
    if (!word)
        return NULL;  // Toujours vérifier l'allocation mémoire

    // Copier le mot dans le tableau
	i = *index;
    for (int j = 0; j < size; j++) {
        word[j] = str[i++];
    }
    word[size] = '\0';  // Ajouter le caractère de fin de chaîne

    *index = i;  // Mettre à jour l'index pour le prochain appel
    return word;
}


t_token	*lexer(char *str)
{
	t_token	*head;
	t_token	*current;
    char *word;
    int i;

	i = 0;
    while (str[i])
    {
        if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        {
            i++;
            continue;
        }
        if (ft_isalpha(str[i]))
        {
			if (head = NULL)
            	head->str = get_word(str, &i);
			else
				current->str = get_word(str, &i);
        }
    }
}

