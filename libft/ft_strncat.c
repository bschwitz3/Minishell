/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:25 by bschwitz          #+#    #+#             */
/*   Updated: 2022/11/28 16:52:05 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*sav_d;

	sav_d = dest;
	while (*dest)
		dest++;
	while (nb && *src)
	{
		*dest++ = *src++;
		nb--;
	}
	*dest = '\0';
	return (sav_d);
}
