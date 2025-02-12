/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:26:30 by mlavergn          #+#    #+#             */
/*   Updated: 2024/08/04 02:46:12 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*stock;

	stock = (void *)malloc(nmemb * size);
	if (!stock)
		return (NULL);
	ft_bzero(stock, (nmemb * size));
	return (stock);
}
