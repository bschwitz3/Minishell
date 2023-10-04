/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:00:39 by bschwitz          #+#    #+#             */
/*   Updated: 2022/12/13 18:02:36 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_first(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	tmp = *lst;
	tmp = tmp->next;
	del((*lst)->content);
	free(*lst);
	*lst = tmp;
}

void	ft_lstdel_last(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*last_node;

	if (!lst || !lst->next)
		return ;
	tmp = lst;
	while (tmp->next->next)
		tmp = tmp->next;
	last_node = tmp->next;
	tmp->next = 0;
	del(last_node->content);
	free(last_node);
}

void	ft_lstdel_middle(t_list **lst, int node_nbr, void (*del)(void*))
{
	int		cur_node;
	t_list	*tmp;
	t_list	*to_delete;

	cur_node = 0;
	tmp = *lst;
	while (cur_node + 1 < node_nbr)
	{
		tmp = tmp->next;
		cur_node++;
	}
	to_delete = tmp->next;
	tmp->next = to_delete->next;
	del(to_delete->content);
	free(to_delete);
}
