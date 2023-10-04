/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:34:19 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:18:48 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(void)
{
	int	check;

	check = 0;
	if (!g_msh.input)
		quit_prog(EXIT_FAILURE);
	check = check_input(g_msh.input);
	return (check);
}

int	check_input(char *input)
{
	int		check;
	char	err_msg[100];

	ft_bzero(err_msg, 0);
	if (*input == '\0' || ft_strisspace((char *)input))
		check = 0;
	else if (!is_input_valid_unexpected_token(input, err_msg)
		|| !is_input_valid_not_supported(input, err_msg))
	{
		check = 0;
		g_msh.exit_status = ENOEXEC;
		write_msh_error(err_msg);
	}
	else
		check = 1;
	return (check);
}

int	is_input_valid_unexpected_token(char *input, char *err_msg)
{
	int	check;

	if (has_quotes_open(input, err_msg)
		|| has_char_at_beginning(input, '|', err_msg)
		|| has_char_at_beginning(input, ';', err_msg)
		|| has_char_at_end(input, '|', err_msg)
		|| has_char_at_end(input, '<', err_msg)
		|| has_char_at_end(input, '>', err_msg)
		|| has_char_at_end(input, '&', err_msg)
		|| has_forbidden_sequence(input, ";;", err_msg)
		|| has_forbidden_sequence(input, "|;", err_msg)
		|| has_forbidden_sequence(input, "&;", err_msg)
		|| has_forbidden_sequence(input, ";|", err_msg)
		|| has_forbidden_sequence(input, ";&", err_msg)
		|| has_forbidden_sequence(input, ">>>", err_msg)
		|| has_spaces_between_char(input, '|', err_msg)
		|| has_spaces_between_char(input, '>', err_msg))
		check = 0;
	else
		check = 1;
	return (check);
}

int	is_input_valid_not_supported(char *input, char *err_msg)
{
	int		check;

	if (has_non_supported(input, "*", err_msg)
		|| has_non_supported(input, "\\", err_msg)
		|| has_non_supported_one(input, "&", err_msg)
		|| has_non_supported(input, ";", err_msg))
		check = 0;
	else
		check = 1;
	return (check);
}
