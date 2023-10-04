/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:06:35 by bschwitz          #+#    #+#             */
/*   Updated: 2021/11/02 17:24:10 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

unsigned int	ft_lennbr(long nbr, int neg)
{
	unsigned int	len;

	if (nbr == 0)
		return (1);
	len = 0;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	if (neg == -1)
		len++;
	return (len);
}

void	ft_inttochar(char *str, long int nbr, unsigned int len, int neg)
{
	str[len] = '\0';
	str[--len] = nbr % 10 + '0';
	nbr = nbr / 10;
	while (nbr > 0)
	{
		str[--len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (neg == -1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		nbr;
	unsigned int	len;
	int				neg;

	neg = 1;
	if (n < 0)
	{
		nbr = (long)n * -1;
		neg = -1;
	}
	else
		nbr = n;
	len = ft_lennbr(nbr, neg);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_inttochar(str, nbr, len, neg);
	return (str);
}
