/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:16:10 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:24:32 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(const char *input, int *curr_pos)
{
	int		has_double_quotes_open;
	int		has_single_quotes_open;

	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (input[*curr_pos])
	{
		if (input[*curr_pos] == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (input[*curr_pos] == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		(*curr_pos)++;
		if (!has_double_quotes_open && !has_single_quotes_open)
			break ;
	}
}

void	skip_spaces(const char *input, int *curr_pos)
{
	while (input[*curr_pos] && ft_isspace(input[*curr_pos]))
		(*curr_pos)++;
}

// comme strstr mais cherche str seulement en dehors des quotes
char	*ft_strstr_quotes(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (!(*to_find))
		return (str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes(str, &i);
		if (!ft_strncmp(&str[i], to_find, ft_strlen(to_find)))
			return (&str[i]);
		if (str[i])
			i++;
	}
	return (0);
}

int	is_quote(char c)
{
	int	check;

	if (c == '"' || c == '\'')
		check = 1;
	else
		check = 0;
	return (check);
}

void	skip_letters(const char *input, int *curr_pos)
{
	if (input[*curr_pos] == '$' || input[*curr_pos] == '/')
		(*curr_pos)++;
	while (input[*curr_pos] && !is_quote(input[*curr_pos])
		&& input[*curr_pos] != '$' && input[*curr_pos] != '/')
		(*curr_pos)++;
}
