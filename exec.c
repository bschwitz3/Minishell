/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:30:59 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 21:14:42 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execute l'input parsé
void	exec_base(t_base *base)
{
	t_list	*cmd_table;

	cmd_table = base->cmd_tables;
	while (cmd_table)
	{	
		g_msh.curr_cmd_table = cmd_table->content;
		exec_cmd_table(g_msh.curr_cmd_table);
		save_last_token(g_msh.curr_cmd_table);
		cmd_table = cmd_table->next;
	}
}

// execute cmds simples de la cmd_table, consécutivement et 
//en redirigent entrée/sortie selon redir et pipe
void	exec_cmd_table(t_cmd_table *cmd_table)
{
	t_list	*cmds;
	int		i;

	cmd_table->return_value = -1;
	cmds = cmd_table->cmds;
	cmd_table->nb_cmds = ft_lstsize(cmds);
	cmd_table->pipes = init_pipes(cmd_table->nb_cmds);
	i = 0;
	while (i < cmd_table->nb_cmds)
	{
		exec_cmd(cmds->content, cmd_table, i);
		cmds = cmds->next;
		i++;
	}
	close_all_pipes(cmd_table->pipes, cmd_table->nb_cmds);
	exec_parent(&cmd_table->pids);
	free_arr((void **)cmd_table->pipes);
	if (cmd_table->return_value != -1)
		g_msh.exit_status = cmd_table->return_value;
}

// check si c'est un relativ path (qui commence par un "." comme ./minishell)
int	has_relative_path(char *first_token)
{
	int	check;

	if (*first_token == '.')
		check = 1;
	else
		check = 0;
	return (check);
}

// check si c'est un absolute path (qui commence par un "/" comme /bin/ls)
int	has_absolute_path(char *first_token)
{
	int	check;

	if (*first_token == '/')
		check = 1;
	else
		check = 0;
	return (check);
}

// execute cmd simple. on crée que 1 process enfant exec_program() ça veut 
//dire qu'on execute sur le process parent car on doit modifié la var d'env 
// pour certaine fonction comme cd,export
void	exec_cmd(t_cmd *cmd, t_cmd_table *cmd_table, int process_index)
{
	int	saved_stdin;
	int	saved_stdout;
	int	nb_cmds;
	int	i;

	nb_cmds = cmd_table->nb_cmds;
	replace_envs(&cmd->tokens, cmd->redirs);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	i = set_redirs_pipes(cmd->redirs, cmd_table, process_index);
	if (i == 2)
		if (exec_cmd2(cmd, cmd_table) == 0)
			return ;
	if (g_msh.exit_status == EXIT_SUCCESS && cmd->tokens != 0)
	{
		if (is_builtin(cmd->tokens))
			exec_builtin(cmd->tokens, &g_msh.dup_env, nb_cmds, process_index);
		else
			exec_program(cmd->tokens, cmd_table);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
