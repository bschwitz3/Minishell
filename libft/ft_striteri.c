/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:44:04 by bschwitz          #+#    #+#             */
/*   Updated: 2021/11/03 15:48:31 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	iter;

	iter = 0;
	if (!s || !f)
		return ;
	while (s[iter] != '\0')
	{
		f(iter, &s[iter]);
		iter++;
	}
}
