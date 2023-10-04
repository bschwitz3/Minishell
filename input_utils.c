/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:35:06 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:32:44 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check si guillemets ouverts
int	has_quotes_open(char *input, char *err_msg)
{
	int	check;
	int	has_dquotes_open;
	int	has_squotes_open;

	check = 1;
	has_dquotes_open = 0;
	has_squotes_open = 0;
	while (*input)
	{
		if (*input == '"' && has_squotes_open == 0)
			has_dquotes_open = !has_dquotes_open;
		else if (*input == '\'' && has_dquotes_open == 0)
			has_squotes_open = !has_squotes_open;
		input++;
	}
	if (has_dquotes_open || has_squotes_open)
	{
		check = 1;
		ft_strcpy(err_msg, "syntax error: open quotes");
	}
	else
		check = 0;
	return (check);
}

// check si char specifique au debut
int	has_char_at_beginning(char *input, char c, char *err_msg)
{
	int		check;
	char	*cpy;

	cpy = ft_strtrim(input, WHITE_SPACE);
	if (!cpy)
		quit_prog(EXIT_FAILURE);
	if (cpy[0] == c)
	{
		check = 1;
		ft_strcpy(err_msg, "syntax error near unexpected token `");
		ft_strncat(err_msg, &c, 1);
		ft_strncat(err_msg, "'", 2);
	}
	else
		check = 0;
	free(cpy);
	return (check);
}

// check si char specifique a la fin
int	has_char_at_end(char *input, char c, char *err_msg)
{
	int		check;
	char	*cpy;
	int		len;

	cpy = ft_strtrim(input, WHITE_SPACE);
	if (!cpy)
		quit_prog(EXIT_FAILURE);
	len = ft_strlen(cpy);
	if (cpy[len - 1] == c)
	{
		check = 1;
		ft_strcpy(err_msg, "syntax error near unexpected token `");
		ft_strncat(err_msg, &c, 1);
		ft_strncat(err_msg, "'", 2);
	}
	else
		check = 0;
	free(cpy);
	return (check);
}

// check si input a erreur de syntaxe sans
// suite : tenir compte des espaces entre implémentation
int	has_forbidden_sequence(char *input, char *test, char *err_msg)
{
	int		check;
	char	*trimmed;

	trimmed = ft_strtrim_all(input, WHITE_SPACE);
	if (!trimmed)
		quit_prog(EXIT_FAILURE);
	if (ft_strstr_quotes(trimmed, test) != 0)
	{
		check = 1;
		ft_strcpy(err_msg, "syntax error near unexpected token `");
		ft_strncat(err_msg, test, 1);
		ft_strcat(err_msg, "'");
	}
	else
		check = 0;
	free(trimmed);
	return (check);
}

// check si un char est trouvé a double avec des espaces entre
int	has_spaces_between_char(char *input, char c, char *err_msg)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			skip_quotes(input, &i);
		if (input[i] == c && input[i + 1] == ' ')
		{
			i++;
			skip_spaces((char *)input, &i);
			if (input[i] == c)
			{
				ft_strcpy(err_msg, "syntax error near unexpected token `");
				ft_strncat(err_msg, &c, 1);
				ft_strcat(err_msg, "'");
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}
