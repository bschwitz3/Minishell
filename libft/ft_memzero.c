/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:55:01 by bschwitz          #+#    #+#             */
/*   Updated: 2022/11/21 17:55:22 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memzero(void *dst, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == 0)
		return (0);
	while (i < n)
	{
		((unsigned char *) dst)[i] = 0;
		i++;
	}
	return (dst);
}
