/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:57:58 by bschwitz          #+#    #+#             */
/*   Updated: 2022/11/21 18:00:56 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *mem, size_t old_size, size_t new_size)
{
	void	*new_mem;
	size_t	copy_size;

	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	new_mem = ft_malloc(new_size);
	ft_memcpy(new_mem, mem, copy_size);
	ft_free(mem);
	return (new_mem);
}
