/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:43:03 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:43:29 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_x_permission(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == EXIT_SUCCESS)
	{
		if (statbuf.st_mode & S_IXUSR)
			return (1);
		else
		{
			write_msh_exec_arg_error("cd", path, "Permission denied");
			return (0);
		}
	}
	else
	{
		write_msh_exec_arg_error("cd", path, strerror(errno));
		return (0);
	}
}

int	cd_path_error_check(char *path)
{
	DIR	*dirp;
	int	status;

	if (!has_x_permission(path))
		return (EXIT_FAILURE);
	dirp = opendir(path);
	if (dirp == NULL)
		status = other_invalid_error("cd", errno, path);
	else
	{
		status = EXIT_SUCCESS;
		closedir(dirp);
	}
	return (status);
}

int	execute_cd(t_list *tokens, t_list **env, char *pwd)
{
	char	*arg;
	int		status;

	if (tokens == 0)
		status = change_dir_home(pwd, env);
	else if (tokens->next != 0)
		status = cd_error_messsage("cd", "too many arguments");
	else
	{
		arg = tokens->content;
		if (!ft_strcmp(arg, "-"))
			status = change_to_old_dir(pwd, env);
		else if (chdir(arg) == EXIT_SUCCESS)
			status = update_directories(pwd, env);
		else
			status = other_invalid_error("cd", errno, arg);
	}
	return (status);
}
