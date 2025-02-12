/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 01:26:48 by mlavergn          #+#    #+#             */
/*   Updated: 2024/08/04 03:00:51 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			s_len;
	size_t			substr_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		substr_len = s_len - start;
	else
		substr_len = len;
	str = malloc(sizeof(char) * (substr_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, substr_len + 1);
	return (str);
}
