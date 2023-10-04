/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:31:42 by bschwitz          #+#    #+#             */
/*   Updated: 2021/11/02 12:14:33 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_is_set(char s, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;
	size_t	i;
	char	*str;

	if (!s1)
		return (ft_strdup(""));
	debut = 0;
	fin = (size_t)ft_strlen(s1);
	i = 0;
	while (s1[debut] && ft_is_set(s1[debut], set))
		debut++;
	while (debut < fin && ft_is_set(s1[fin - 1], set))
		fin--;
	str = malloc(sizeof(char) * (fin - debut + 1));
	if (!str)
		return (0);
	while (debut < fin)
	{
		str[i] = s1[debut];
		i++;
		debut++;
	}
	str[i] = '\0';
	return (str);
}
