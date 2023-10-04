/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:17:39 by bschwitz          #+#    #+#             */
/*   Updated: 2021/10/28 17:03:18 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	j = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = dstlen;
	if (dstsize == 0)
		return (srclen);
	else if (dstsize < dstlen)
		return (srclen + dstsize);
	else
	{
		while (src[j] != '\0' && (dstlen + j) < dstsize)
			dst[i++] = src[j++];
		if ((dstlen + j) == dstsize && dstlen < dstsize)
			dst[i - 1] = '\0';
		else
			dst[i] = '\0';
		return (srclen + dstlen);
	}
}
