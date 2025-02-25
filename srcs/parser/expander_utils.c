/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:08:48 by mlavergn          #+#    #+#             */
/*   Updated: 2025/02/25 17:12:22 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	*ft_strjoin_char_free(char *s, char c)
{
	char	*new_str;
	int		len;

	if (!s)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}
