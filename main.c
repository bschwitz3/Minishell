/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 23:26:24 by snadji-h          #+#    #+#             */
/*   Updated: 2023/01/12 21:14:57 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	g_msh;

void	init_msh(t_msh *msh, char **envp)
{
	ft_bzero(msh, sizeof(t_msh));
	dupli_env(&msh->dup_env, envp);
	unset_oldpwd();
	increment_shlvl();
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
	g_msh.redir = malloc(sizeof(t_redir));
}

int	main(int ac, char **av, char **envp)
{
	char	*prompt;

	(void)ac;
	(void)av;
	init_msh(&g_msh, envp);
	while (1)
	{
		prompt = write_prompt();
		g_msh.input = readline(prompt);
		if (!get_input())
			continue ;
		g_msh.base = get_base();
		exec_base(g_msh.base);
		add_history(g_msh.input);
		free(g_msh.input);
		g_msh.base = 0;
	}
	return (0);
}
