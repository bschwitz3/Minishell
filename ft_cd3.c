/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:41:59 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:42:54 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir_home(char *cur_pwd, t_list **env)
{
	int		status;
	char	*home;

	home = getenv("HOME");
	if (home == 0)
	{
		write_msh_exec_error("cd", "HOME not set");
		status = EXIT_FAILURE;
	}
	else if (*home == '\0')
		status = EXIT_SUCCESS;
	else
	{
		if (chdir(home) == 0)
			status = update_directories(cur_pwd, env);
		else
			status = other_invalid_error("cd", errno, home);
		home = EXIT_SUCCESS;
	}
	if (home)
		free(home);
	return (status);
}

int	change_to_old_dir(char *cur_pwd, t_list **env)
{
	char	*old_dir;
	int		status;

	old_dir = getenv("OLDPWD");
	if (old_dir == 0 || *old_dir == '\0')
	{
		write_msh_exec_error("cd", "OLDPWD not set");
		status = EXIT_FAILURE;
	}
	else
	{
		if (chdir(old_dir) == 0)
		{
			printf("%s\n", old_dir);
			status = update_directories(cur_pwd, env);
		}
		else
			status = other_invalid_error("cd", errno, old_dir);
	}
	if (old_dir)
		free(old_dir);
	return (status);
}

int	update_directories(char *old_dir, t_list **env)
{
	char	new_dir[MAX_PATH];

	if (getcwd(new_dir, MAX_PATH) == NULL)
		return (EXIT_FAILURE);
	if (!is_env_var("PWD", *env))
		create_environment_var("PWD", env);
	update_environment_var("PWD", new_dir, *env);
	if (!is_env_var("OLDPWD", *env))
		create_environment_var("OLDPWD", env);
	update_environment_var("OLDPWD", old_dir, *env);
	return (EXIT_SUCCESS);
}

void	create_environment_var(char *token_str, t_list **env)
{
	t_list	*new_var;
	char	*new_var_str;
	t_list	*temp_last;

	temp_last = ft_lstlast(*env);
	new_var_str = ft_strdup(token_str);
	if (new_var_str == 0)
		quit_prog(EXIT_FAILURE);
	new_var = ft_lstnew(new_var_str);
	if (new_var == 0)
		quit_prog(EXIT_FAILURE);
	ft_lstadd_before_back(env, new_var);
	ft_lstadd_back(env, temp_last);
}
