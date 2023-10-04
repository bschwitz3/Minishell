/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:19:30 by bschwitz          #+#    #+#             */
/*   Updated: 2021/10/28 17:05:35 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
			i++;
	}
	else
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
