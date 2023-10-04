/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:02:37 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 14:00:51 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_list *tokens)
{
	char	pwd[MAX_PATH];

	if (!tokens->next)
	{
		if (getcwd(pwd, MAX_PATH) == NULL)
			return (EXIT_FAILURE);
		printf("%s\n", pwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		write_msh_exec_error("pwd", "too many arguments");
		return (EXIT_FAILURE);
	}
}
