/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:23:55 by bschwitz          #+#    #+#             */
/*   Updated: 2022/12/14 18:24:48 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new_lst;
	t_list	*tmp;

	new_lst = 0;
	while (lst)
	{
		tmp = ft_lstnew(lst->content);
		if (!tmp)
			return (0);
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}
