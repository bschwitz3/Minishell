/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:20:27 by bschwitz          #+#    #+#             */
/*   Updated: 2022/11/30 15:43:19 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strisspace(char *str)
{
	int	check;

	if (!str || !(*str))
		return (0);
	check = 1;
	while (*str)
	{
		if (!ft_isspace(*str))
		{
			check = 0;
			break ;
		}
		str++;
	}
	return (check);
}
