/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:29:09 by bschwitz          #+#    #+#             */
/*   Updated: 2022/12/14 18:21:40 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clear;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		clear = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = clear;
	}
}

void	ft_lstdel_int(void *data)
{
	(void)data;
}

void	ft_lstclear_if(t_list **lst, int (*cmp)(void *), void (*del)(void *))
{
	if (!lst)
		return ;
	while (*lst)
	{
		if (cmp((*lst)->content))
			ft_lstdel_first(lst, del);
		else
			lst = &(*lst)->next;
	}
}
