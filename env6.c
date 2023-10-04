/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:05:04 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:06:46 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_value(char	*key)
{
	int		i;
	t_list	*envp;
	char	*curr_envp;

	envp = g_msh.dup_env;
	while (envp)
	{
		i = 0;
		curr_envp = (char *)envp->content;
		while (key[i] && curr_envp[i] && (key[i] == curr_envp[i]))
			i++;
		if (!key[i] && curr_envp[i] == '=')
		{
			replace_string(key, &curr_envp);
			envp->content = curr_envp;
		}
		envp = envp->next;
	}
	return ;
}

void	replace_string(char *src, char **dest)
{
	char	*temp;

	temp = ft_strdup(src);
	if (temp == 0)
		quit_prog(EXIT_FAILURE);
	free(*dest);
	*dest = 0;
	*dest = temp;
}

void	increment_shlvl(void)
{
	char	*cur_lvl;
	int		lvl_nbr;

	if (is_env_var("SHLVL", g_msh.dup_env) == 0)
		create_environment_var("SHLVL=1", &g_msh.dup_env);
	else
	{
		cur_lvl = getenv("SHLVL");
		lvl_nbr = ft_atoi(cur_lvl);
		lvl_nbr++;
		cur_lvl = ft_itoa(lvl_nbr);
		if (cur_lvl == 0)
			quit_prog(EXIT_FAILURE);
		update_environment_var("SHLVL", cur_lvl, g_msh.dup_env);
		free(cur_lvl);
	}
}
