/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:09:23 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:30:10 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// crée tab d'int, chaque dimension est un pipe. il y aura 2 ints :
// [0] = read la fin du pipe
// [1] = write la fin du pipe
int	**init_pipes(int nb_cmds)
{
	int	**pipes;
	int	i;

	if (nb_cmds == 1)
		return (0);
	pipes = ft_calloc(nb_cmds, sizeof(int *));
	if (!pipes)
		quit_prog(EXIT_FAILURE);
	i = 0;
	while (i < nb_cmds - 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			quit_prog(EXIT_FAILURE);
		if (pipe(pipes[i]) == -1)
			quit_prog(EXIT_FAILURE);
		i++;
	}
	return (pipes);
}

// ferme les pipes de init_pipe
void	close_all_pipes(int **pipes, int nb_cmds)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = nb_cmds - 1;
	while (i < nb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

// ajuste le parsing pour facilité pipe/redir , redir priorité sur pipe
int	set_redirs_pipes(t_list *redirs,
						t_cmd_table *cmd_table,
						int process_index)
{
	int	**pipes;
	int	nb_cmds;

	pipes = cmd_table->pipes;
	nb_cmds = cmd_table->nb_cmds;
	if (open_all_files(redirs) == EXIT_FAILURE)
		return (1);
	if (has_redirs(redirs, "<<"))
		return (2);
	if (!has_redirs(redirs, "<") && process_index != 0)
		dup2(pipes[process_index - 1][0], STDIN_FILENO);
	if (!has_redirs(redirs, ">") && !has_redirs(redirs, ">>")
		&& process_index != nb_cmds - 1)
		dup2(pipes[process_index][1], STDOUT_FILENO);
	g_msh.exit_status = EXIT_SUCCESS;
	return (0);
}

// check si il y a redirection
int	has_redirs(t_list *redirs, char *type)
{
	int		check;
	t_redir	*redir;

	check = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (!ft_strcmp(redir->type, type))
		{
			check = 1;
			break ;
		}
		redirs = redirs->next;
	}
	return (check);
}

int	open_all_files(t_list *redirs)
{
	int		fd_i;
	int		fd_o;
	t_redir	*redir;

	fd_i = -2;
	fd_o = -2;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (!ft_strcmp(redir->type, "<"))
			fd_i = open_file(redir, fd_i, O_RDONLY, 0);
		else if (!ft_strcmp(redir->type, ">"))
			fd_o = open_file(redir, fd_o, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (!ft_strcmp(redir->type, ">>"))
			fd_o = open_file(redir, fd_o, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd_i == -1 || fd_o == -1)
			return (EXIT_FAILURE);
		redirs = redirs->next;
	}
	return (EXIT_SUCCESS);
}
