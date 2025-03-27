/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:47 by mlavergn          #+#    #+#             */
/*   Updated: 2025/03/27 15:06:32 by mlavergn         ###   ########.fr       */
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
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
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
	char	*to_add;

	if (!(*str)[*i + 1] || (*str)[*i + 1] == ' ')
		to_add = ft_strdup("$");
	else if ((*str)[*i + 1] == '?')
	{
		to_add = ft_itoa(g_env.last_exit);
		(*i)++;
	}
	else
	{
		value = get_word(&(*str)[*i]);
		printf("%s\n", value);
		to_add = extract_word_env(g_env.env, value + 1);
		printf("%s\n", to_add);
		*i += ft_strlen(value) - 1;
		free(value);
	}
	*new_str = ft_strjoin_free(*new_str, to_add);
	printf("%s\n", *new_str);
	free(to_add);
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
			continue ;
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
