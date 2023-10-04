/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:06 by bschwitz          #+#    #+#             */
/*   Updated: 2022/11/21 17:54:41 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// TEST ligne 25 a afficher les malloc : printf("Malloc %p(%zu)\n", mem, size);
void	*ft_malloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
	{
		printf("Error allocation\n");
		exit (1);
	}
	ft_memzero(mem, size);
	return (mem);
}
