/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:14:06 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/24 23:22:36 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_word(char *str)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != 32 && str[len] != '\"' && str[len] != '\'')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*extract_word_env(char **env, const char *value)
{
	int		i;
	size_t	value_len;
	char	*new_value;

	new_value = NULL;
	value_len = ft_strlen(value);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], value, value_len) == 0 && env[i][value_len] == '=')
		{
			new_value = ft_strchr(env[i], '=');
			break ;
		}
		i++;
	}
	if (!new_value)
		return (ft_strdup(""));
	return (ft_strdup(new_value + 1));
}

char	*ft_strreplace(char *str, char *old, char *new)
{
	char	*pos;
	char	*result;
	size_t	len;

	pos = ft_strnstr(str, old, ft_strlen(str));
	if (!str || !old || !new || !pos)
	{
		if (str)
			return (ft_strdup(str));
		return (NULL);
	}
	len = (pos - str) + ft_strlen(new) + ft_strlen(pos + ft_strlen(old));
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, pos - str + 1);
	ft_strlcpy(result + (pos - str), new, ft_strlen(new) + 1);
	ft_strlcpy(result + (pos - str)
		+ ft_strlen(new), pos + ft_strlen(old), len + 1);
	return (result);
}

void	expand_dollar(char	**str, char **env)
{
	char	*value;
	char	*extracted_value;
	char	*new_str;

	value = get_word(ft_strchr(*str, '$'));
	if (!value)
		return ;
	extracted_value = extract_word_env(env, value + 1);
	new_str = ft_strreplace(*str, value, extracted_value);
	free(*str);
	*str = ft_strdup(new_str);
	free(new_str);
	free(value);
	free(extracted_value);
	if (ft_strchr(*str, '$'))
		expand_dollar(str, env);
}

void	parser2(t_token **tokens, char **env)
{
	char	*temp;
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (!(current->str[0] == '\''
				&& current->str[ft_strlen(current->str) - 1] == '\''))
			expand_dollar(&current->str, env);
		if (current->str[0] == '\"' || current->str[0] == '\'')
		{
			temp = ft_substr(current->str, 1, ft_strlen(current->str) - 2);
			free(current->str);
			current->str = ft_strdup(temp);
			free(temp);
		}
		current = current->next;
	}
	print_tokens(*tokens);
	free_tokens(*tokens);
}
