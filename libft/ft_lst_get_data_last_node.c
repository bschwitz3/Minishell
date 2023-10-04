/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_data_last_node.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:59:47 by bschwitz          #+#    #+#             */
/*   Updated: 2022/12/08 17:01:53 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// aller au dernier de la liste
void	*ft_lst_get_data_last_node(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst->content);
}
