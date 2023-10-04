/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:43:39 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:15:06 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// liste basique ou l'input et séparée token par token
t_base	*get_base(void)
{
	t_base	*base;
	t_list	*cmd_table;
	int		curr_pos;

	base = ft_calloc(1, sizeof(t_base));
	if (!base)
		quit_prog(EXIT_FAILURE);
	curr_pos = 0;
	while (g_msh.input[curr_pos])
	{
		skip_spaces(g_msh.input, &curr_pos);
		cmd_table = ft_lstnew((void *)get_cmd_table(&curr_pos));
		if (!cmd_table)
			quit_prog(EXIT_FAILURE);
		ft_lstadd_back(&base->cmd_tables, cmd_table);
	}
	return (base);
}

// chaque commande "simple" separé par pipe a sa propre 
// liste avec ses option, args,..
t_cmd_table	*get_cmd_table(int *curr_pos)
{
	t_cmd_table	*cmd_table;
	t_list		*cmd;

	cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (!cmd_table)
		quit_prog(EXIT_FAILURE);
	while (g_msh.input[*curr_pos])
	{
		skip_spaces(g_msh.input, curr_pos);
		cmd = ft_lstnew((void *)get_cmd(curr_pos));
		if (!cmd)
			quit_prog(EXIT_FAILURE);
		ft_lstadd_back(&cmd_table->cmds, cmd);
		if (g_msh.input[*curr_pos] == '|' && g_msh.input[*curr_pos + 1] != '|')
			(*curr_pos)++;
	}
	return (cmd_table);
}

// prend une commande qui est juste une série de token ou de redir
t_cmd	*get_cmd(int *curr_pos)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		quit_prog(EXIT_FAILURE);
	while (g_msh.input[*curr_pos] && !is_cmd_delimiter(g_msh.input[*curr_pos]))
	{
		if (g_msh.input[*curr_pos] != '>' && g_msh.input[*curr_pos] != '<')
		{
			new_node = ft_lstnew((void *)get_token(curr_pos));
			if (!new_node)
				quit_prog(EXIT_FAILURE);
			ft_lstadd_back(&cmd->tokens, new_node);
		}
		else if (g_msh.input[*curr_pos] == '>' || g_msh.input[*curr_pos] == '<')
		{
			new_node = ft_lstnew((void *)get_redir(curr_pos));
			if (!new_node)
				quit_prog(EXIT_FAILURE);
			ft_lstadd_back(&cmd->redirs, new_node);
		}
		skip_spaces(g_msh.input, curr_pos);
	}
	return (cmd);
}

// isole un token, un argument, ça peut être un mot ou plusieurs si ""
char	*get_token(int *curr_pos)
{
	char	*token;
	int		saved_pos;

	saved_pos = *curr_pos;
	while (g_msh.input[*curr_pos]
		&& !is_token_delimiter(g_msh.input[*curr_pos]))
	{
		if (is_quote(g_msh.input[*curr_pos]))
			skip_quotes(g_msh.input, curr_pos);
		else if (g_msh.input[*curr_pos])
			(*curr_pos)++;
	}
	token = ft_substr(g_msh.input, saved_pos, *curr_pos - saved_pos);
	if (!token)
		quit_prog(EXIT_FAILURE);
	return (token);
}

// prend une redirection
t_redir	*get_redir(int *curr_pos)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		quit_prog(EXIT_FAILURE);
	if (!ft_strncmp(&g_msh.input[*curr_pos], ">>", 2))
	{
		ft_strncpy(redir->type, (char *)&g_msh.input[*curr_pos], 2);
		*curr_pos += 2;
	}
	else if (!ft_strncmp(&g_msh.input[*curr_pos], "<<", 2))
	{
		ft_strncpy(redir->type, (char *)&g_msh.input[*curr_pos], 2);
		*curr_pos += 2;
	}
	else if (g_msh.input[*curr_pos] == '<')
		*redir->type = g_msh.input[(*curr_pos)++];
	else if (g_msh.input[*curr_pos] == '>')
		*redir->type = g_msh.input[(*curr_pos)++];
	skip_spaces(g_msh.input, curr_pos);
	redir->direction = get_token(curr_pos);
	g_msh.redir->direction = redir->direction;
	return (redir);
}
