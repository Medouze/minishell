/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 23:00:52 by mlavergn          #+#    #+#             */
/*   Updated: 2024/08/03 23:38:41 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	nbr;

	nbr = n;
	size = nbr_len(nbr);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	str[size--] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		str[size--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
