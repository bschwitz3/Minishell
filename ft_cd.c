/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:28:00 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:47:09 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_list *tokens, t_list **env)
{
	char	pwd[MAX_PATH];

	if (getcwd(pwd, MAX_PATH) == NULL)
	{
		write_msh_exec_error("cd", strerror(errno));
		return (errno);
	}
	if (!has_only_one_cmd())
		return (only_cd_errors(tokens));
	else
		return (execute_cd(tokens, env, pwd));
}

int	only_cd_errors(t_list *tokens)
{
	char	*arg;
	int		status;

	status = 0;
	if (tokens == 0)
		status = cd_env_error_check("HOME");
	else if (tokens->next != 0)
		status = cd_error_messsage("cd", "too many arguments");
	else
	{
		arg = tokens->content;
		if (ft_strcmp(arg, "-") == 0)
			status = cd_env_error_check("OLDPWD");
		else
			status = cd_path_error_check(arg);
	}
	return (status);
}

int	cd_env_error_check(char *env)
{
	DIR		*dirp;
	char	*arg;
	int		status;

	arg = getenv(env);
	if (arg == 0)
		status = cd_error_messsage("cd", "HOME not set");
	else if (*arg == '\0')
		status = EXIT_SUCCESS;
	else
	{
		if (!has_x_permission(arg))
			return (EXIT_FAILURE);
		dirp = opendir(arg);
		if (dirp == NULL)
			status = other_invalid_error("cd", errno, arg);
		else
		{
			status = EXIT_SUCCESS;
			closedir(dirp);
		}
		free(arg);
	}
	return (status);
}

int	cd_error_messsage(char *builtin, char *error)
{
	write_msh_exec_error(builtin, error);
	return (EXIT_FAILURE);
}

int	other_invalid_error(char *builtin, int error, char *arg)
{
	write_msh_exec_arg_error(builtin, arg, strerror(error));
	return (EXIT_FAILURE);
}
