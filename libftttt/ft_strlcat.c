/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:13:40 by mlavergn          #+#    #+#             */
/*   Updated: 2024/08/03 16:45:17 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_size;

	i = 0;
	dst_size = 0;
	while (dst[dst_size] && dst_size < size)
		dst_size++;
	while (dst_size + i + 1 < size && src[i])
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	if (dst_size != size)
		dst[dst_size + i] = '\0';
	return (dst_size + ft_strlen(src));
}
