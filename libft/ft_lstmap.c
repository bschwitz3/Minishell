/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:51:46 by bschwitz          #+#    #+#             */
/*   Updated: 2021/11/09 15:20:21 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;

	if (!lst)
		return (0);
	map = ft_lstnew(f(lst->content));
	if (!map)
		return (0);
	if (lst->next != 0)
		map->next = ft_lstmap(lst->next, *(*f), *del);
	return (map);
}
