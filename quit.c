/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:54:14 by snadji-h          #+#    #+#             */
/*   Updated: 2023/01/12 18:46:34 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(void *redir)
{
	free(((t_redir *)redir)->direction);
	free(redir);
}

void	free_cmd(void *cmd)
{
	ft_lstclear(&((t_cmd *)cmd)->tokens, free);
	ft_lstclear(&((t_cmd *)cmd)->redirs, free_redir);
	free(cmd);
}

void	free_cmd_table(void *cmd_table)
{
	ft_lstclear(&((t_cmd_table *)cmd_table)->cmds, free_cmd);
	free(cmd_table);
}

void	free_base(t_base *base)
{
	ft_lstclear(&base->cmd_tables, free_cmd_table);
	free(base);
}

void	free_msh(t_msh *msh)
{
	ft_lstclear(&msh->dup_env, free);
	if (msh->base != 0)
		free_base(msh->base);
}
