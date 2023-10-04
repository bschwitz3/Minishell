/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:31:12 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:06:09 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_sigint(int signum)
{
	char	*prompt;

	(void)signum;
	printf("\n");
	prompt = write_prompt();
	g_msh.input = readline(prompt);
}

void	catch_sigquit(int signum)
{
	(void)signum;
	kill(0, SIGCHLD);
}
