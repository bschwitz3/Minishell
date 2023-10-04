/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:58:51 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 14:02:00 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_list *args)
{
	char	*arg;

	if (has_only_one_cmd())
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args == 0 && has_only_one_cmd())
		quit_prog(g_msh.exit_status);
	else if (args == 0 && !has_only_one_cmd())
		return (EXIT_SUCCESS);
	arg = args->content;
	if (ft_strisnumber(arg) && args->next != 0)
		write_msh_exec_error("exit", "too many arguments");
	else if (!ft_strisnumber(arg))
	{
		write_msh_exec_arg_error("exit", arg, "numeric argument required");
		if (has_only_one_cmd())
			quit_prog(EXIT_GENERAL_ERROR);
		else
			return (EXIT_GENERAL_ERROR);
	}
	else if (ft_strisnumber(arg) && args->next == 0 && has_only_one_cmd())
		quit_prog(ft_atoi(arg));
	else if (ft_strisnumber(arg) && args->next == 0 && !has_only_one_cmd())
		return (ft_atoi(arg));
	return (EXIT_FAILURE);
}
