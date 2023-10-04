/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:18 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:38:07 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printf("line : %i in %s \n", __LINE__, __FILE__);

int	make_heredocs(t_cmd *cmd)
{
	while (cmd->redirs->content)
	{
		if (check_heredoc(cmd) == 1)
		{
			return (1);
		}
		cmd->redirs->content = cmd->redirs->next;
	}
	return (0);
}

int	check_heredoc(t_cmd *cmd)
{
	while (cmd->redirs->content)
	{
		if (cmd->redirs->content)
		{
			if (redir_heredoc(cmd) == 1)
				return (1);
		}
		cmd->redirs->content = cmd->redirs->next;
	}
	return (0);
}

int	redir_heredoc(t_cmd	*cmd)
{
	int		new_fd[2];
	pid_t	pid;
	int		wstatus;

	signal(SIGINT, nothing);
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(cmd->redirs->content, new_fd);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_msh.exit_status = WEXITSTATUS(wstatus);
	dup2(new_fd[0], STDIN_FILENO);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
	{
		return (1);
	}
	return (0);
}

void	heredoc(char *limiter, int *fd)
{
	char	*line;

	limiter = g_msh.redir->direction;
	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	free(g_msh.redir->direction);
	exit(EXIT_SUCCESS);
}

void	nothing(int signal)
{
	(void)signal;
}
