/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:22:30 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:24:26 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_delimiter(char c)
{
	int	check;

	if (ft_strchr(WHITE_SPACE, c) != 0)
		check = 1;
	else if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else if (c == '<')
		check = 1;
	else if (c == '>')
		check = 1;
	else
		check = 0;
	return (check);
}

// check si c'est un path absolut et si c'est un fichier
int	is_path_executable(char *exec_file)
{
	struct stat	statbuf;

	if (has_absolute_path(exec_file)
		&& (stat(exec_file, &statbuf) == EXIT_SUCCESS
			|| S_ISREG(statbuf.st_mode)))
		return (1);
	else
		return (0);
}

void	delete_quotes(char *token)
{
	int	i;
	int	has_double_quotes_open;
	int	has_single_quotes_open;

	i = 0;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (token[i])
	{
		if (token[i] == '"' && has_single_quotes_open == 0)
		{
			has_double_quotes_open = !has_double_quotes_open;
			ft_strcpy(&token[i], (const char *)&token[i + 1]);
			continue ;
		}
		else if (token[i] == '\'' && has_double_quotes_open == 0)
		{
			has_single_quotes_open = !has_single_quotes_open;
			ft_strcpy(&token[i], (const char *)&token[i + 1]);
			continue ;
		}
		i++;
	}
}

int	is_cmd_delimiter(char c)
{
	int	check;

	if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else
		check = 0;
	return (check);
}
