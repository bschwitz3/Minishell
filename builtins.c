/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:50:34 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:12:42 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check si cmd est un builtin
int	is_builtin(t_list *tokens)
{
	int		check;
	char	*program_name;

	program_name = tokens->content;
	if (ft_strcmp(program_name, "exit") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "echo") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "env") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "cd") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "pwd") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "export") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "unset") == 0)
		check = 1;
	else
		check = 0;
	return (check);
}
