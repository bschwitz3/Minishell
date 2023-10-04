/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:15:07 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:32:58 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tunning de couleur pour voire si la commande a marcher
char	*write_prompt(void)
{
	char	*prompt;

	if (g_msh.exit_status == EXIT_SUCCESS)
		prompt = "\033[0;32mminishell> \033[0m";
	else
		prompt = "\033[0;31mminishell> \033[0m";
	return (prompt);
}
