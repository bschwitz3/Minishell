/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:53:40 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:56:04 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check si il n'y a qu'une seule commande 
//(parsque certain prog s'execute seulement si 1 cmd)
int	has_only_one_cmd(void)
{
	int	check;

	if (ft_lstsize(g_msh.curr_cmd_table->cmds) == 1)
		check = 1;
	else
		check = 0;
	return (check);
}

// va au travers des token et redir et remplace les var d'env par leurs valeures
void	replace_envs(t_list **tokens, t_list *redirs)
{
	t_list	*token;
	t_redir	*redir;

	token = *tokens;
	while (token)
	{
		replace_env_single_token((char **)&token->content);
		token = token->next;
	}
	if (ft_lstsize(*tokens) > 1 && (char)*((char *)(*tokens)->content) != '\0')
		ft_lstclear_if(tokens, is_token_empty, free);
	while (redirs)
	{
		redir = redirs->content;
		replace_env_single_token(&redir->direction);
		redirs = redirs->next;
	}
}

// remplace token dans le cas d'une variable globale ou char speciaux
void	replace_env_single_token(char **token)
{
	t_list	*split_token;
	t_list	*tmp;
	char	*token_piece;

	split_token = get_split_token(*token);
	tmp = split_token;
	while (tmp)
	{
		token_piece = tmp->content;
		if (!ft_strcmp(token_piece, "~") || !ft_strncmp(token_piece, "~/", 2))
			replace_tilde_with_home((char **)&tmp->content);
		else if (*token_piece != '\'')
		{
			if (*token_piece == '$' && ft_strcmp(token_piece, "$_") != 0
				&& ft_strcmp(token_piece, "$?") != 0 && *(token_piece + 1) != 0)
				replace_one_var((char **)&tmp->content);
			else
				replace_vars_with_values((char **)&tmp->content);
			replace_status_env((char **)&tmp->content, g_msh.exit_status);
		}
		delete_quotes((char *)tmp->content);
		tmp = tmp->next;
	}
	*token = join_split_token(split_token);
}
