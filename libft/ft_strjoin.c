/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:58:53 by bschwitz          #+#    #+#             */
/*   Updated: 2021/11/02 11:31:19 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	len = i + j + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (0);
	ft_memmove(str, s1, i);
	ft_memmove(str + i, s2, j);
	str[len - 1] = '\0';
	return (str);
}
