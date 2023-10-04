/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:00:11 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 20:00:37 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(char *program_name)
{
	char	**path_env_split;
	char	*absolute_path;

	path_env_split = get_path_env_split();
	if (!path_env_split)
	{
		absolute_path = ft_strdup(program_name);
		if (!absolute_path)
			quit_prog(EXIT_FAILURE);
	}
	else
	{
		absolute_path = get_correct_path(program_name, path_env_split);
		free_arr((void **)path_env_split);
	}
	return (absolute_path);
}

char	**get_path_env_split(void)
{
	char	*path_env;
	char	**path_env_split;

	path_env = getenv("PATH");
	if (!path_env)
		return (0);
	path_env_split = ft_split(path_env, ':');
	if (!path_env_split)
		quit_prog(EXIT_FAILURE);
	add_slash(&path_env_split);
	return (path_env_split);
}

void	add_slash(char ***path_env_split)
{
	int		i;
	char	*path;
	int		len;
	char	*new_path;

	i = 0;
	while ((*path_env_split)[i])
	{
		path = (*path_env_split)[i];
		len = ft_strlen(path);
		if (path[len - 1] != '/')
		{
			new_path = ft_strjoin(path, "/");
			free(path);
			(*path_env_split)[i] = new_path;
		}
		i++;
	}
}

char	*get_correct_path(char *program_name, char **path_env_split)
{
	char		*absolute_path;
	int			i;
	struct stat	statbuf;

	i = 0;
	while (path_env_split[i])
	{
		absolute_path = ft_strjoin(path_env_split[i], program_name);
		if (!absolute_path)
			quit_prog(EXIT_FAILURE);
		if (stat(absolute_path, &statbuf) == EXIT_SUCCESS)
			break ;
		free(absolute_path);
		i++;
	}
	if (!path_env_split[i])
	{
		absolute_path = ft_strdup(program_name);
		if (!absolute_path)
			quit_prog(EXIT_FAILURE);
	}
	return (absolute_path);
}

// attends que les processus enfants soit fini et met le exit_status
void	exec_parent(t_list **pids)
{
	long	pid;
	int		exit_info;

	exit_info = 0;
	while (*pids)
	{
		pid = (long)(*pids)->content;
		waitpid(pid, &exit_info, 0);
		if (WIFEXITED(exit_info))
			g_msh.exit_status = WEXITSTATUS(exit_info);
		else if (WIFSIGNALED(exit_info))
			g_msh.exit_status = WTERMSIG(exit_info);
		ft_lstdel_first(pids, ft_lstdel_int);
	}
}
