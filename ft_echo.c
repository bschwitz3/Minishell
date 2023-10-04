/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:09:54 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 14:01:36 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_list *tokens)
{
	int		line_break;
	int		flag_time;
	char	*arg;

	flag_time = 1;
	line_break = 1;
	while (tokens)
	{
		arg = tokens->content;
		if (flag_time && arg[0] == '-' && has_repeated_char_in_str('n', arg, 1))
			line_break = 0;
		else
		{
			if (!flag_time)
				ft_putchar_fd(' ', STDOUT_FILENO);
			flag_time = 0;
			ft_putstr_fd(arg, STDOUT_FILENO);
		}
		tokens = tokens->next;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	has_repeated_char_in_str(char repeat_chr, char *str, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (str[i])
	{
		if (str[i] != repeat_chr)
			return (0);
		i++;
	}
	return (1);
}
