/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:47 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/20 13:58:43 by mlavergn         ###   ########.fr       */
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
	if (str[0] == '$')
		len++;
	while (str[len] && str[len] != 32 && !ft_strchr(SPE_CHARS, str[len])
		&& str[len] != '\'' && str[len] != '"')
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

void	replace_dollar_word(char **str, char **new_str, t_shell g_env, int *i)
{
	char	*value;
	char	*extracted_value;
	char	*first_word;

	if (!(*str)[*i + 1] || (*str)[*i + 1] == 32)
	{
		*new_str = ft_strdup("$");
		return ;
	}
	if ((*str)[*i + 1] == '?')
	{
		first_word = ft_itoa(g_env.last_exit);
		*new_str = ft_strjoin_free(*new_str, first_word);
		free(first_word);
		(*i)++;
	}
	else
	{
		value = get_word(&(*str)[*i]);
		if (value)
		{
			extracted_value = extract_word_env(g_env.env, value + 1);
			*new_str = ft_strjoin_free(*new_str, extracted_value);
			*i += ft_strlen(value) - 1;
			free(value);
			free(extracted_value);
		}
	}
}

void	expand_dollar(char **str, t_shell g_env)
{
	char	*new_str;
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_double = 0;
	in_single = 0;
	new_str = ft_strdup("");
	while ((*str)[i])
	{
		in_quotes(str, i, &in_double, &in_single);
		if ((*str)[i] == '$' && ft_isdigit((*str)[i + 1]) && !in_single)
		{
			i += 2;
			continue;
		}
		else if ((*str)[i] == '$' && (*str)[i + 1] && !in_single)
			replace_dollar_word(str, &new_str, g_env, &i);
		else
			new_str = ft_strjoin_char_free(new_str, (*str)[i]);
		
		i++;
	}
	free(*str);
	*str = new_str;
}

void	expand_tilde(char **path, t_shell g_env)
{
	char	*home;
	char	*expanded;

	home = get_var(g_env.env, "HOME");
	if (((*path)[1] == '/' && !inside_quotes(*path)) ||
		((*path)[1] == '\0' && !inside_quotes(*path)))
	{
		expanded = ft_strjoin(home, (*path) + 1);
		free(home);
		free(*path);
		*path = expanded;
		return ;
	}
	free(home);
}
