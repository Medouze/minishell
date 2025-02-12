/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:49:42 by mlavergn          #+#    #+#             */
/*   Updated: 2024/08/03 20:17:22 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (little[j] && big[i + j] == little[j] && i + j < len)
				j++;
			if (!little[j])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
