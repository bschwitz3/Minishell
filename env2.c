/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:28:50 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:07:15 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// divise un token en plusieurs parties
t_list	*get_split_token(char *token)
{
	t_list	*split_token;
	t_list	*new_node;
	char	*token_piece;
	int		curr_pos;
	int		saved_pos;

	split_token = 0;
	curr_pos = 0;
	saved_pos = 0;
	while (token[curr_pos])
	{
		saved_pos = curr_pos;
		if (is_quote(token[curr_pos]))
			skip_quotes((const char *)token, &curr_pos);
		else
			skip_letters((const char *)token, &curr_pos);
		token_piece = ft_substr(token, saved_pos, curr_pos - saved_pos);
		if (!token_piece)
			quit_prog(EXIT_FAILURE);
		new_node = ft_lstnew((void *)token_piece);
		if (!new_node)
			quit_prog(EXIT_FAILURE);
		ft_lstadd_back(&split_token, new_node);
	}
	return (split_token);
}

void	replace_tilde_with_home(char **token)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (!token[0][1])
	{
		free(*token);
		*token = home_path;
	}
	else
		tilde_join(token, &home_path);
}

// joins le chemin de Home avec le reste de la string
void	tilde_join(char **str, char **home_path)
{
	char	*temp;

	temp = ft_strjoin(*home_path, &str[0][1]);
	if (!temp)
		quit_prog(EXIT_FAILURE);
	free(*home_path);
	*home_path = 0;
	free(*str);
	*str = 0;
	*str = temp;
}

// remplace var $ENV, si sans guillemets, espaces ne doivent pas être imprimés
void	replace_one_var(char **str)
{
	char	*env;
	char	*trimmed;

	env = getenv(*str + 1);
	if (!env)
	{
		free(*str);
		*str = ft_strdup("");
		if (!*str)
			quit_prog(EXIT_FAILURE);
		return ;
	}
	trimmed = ft_strtrim(env, " ");
	if (!trimmed)
		quit_prog(EXIT_FAILURE);
	free(*str);
	*str = trimmed;
}

// trouve le signe dollars et le remplace par sa valeur
void	replace_vars_with_values(char **str)
{
	int		i;
	char	*var;
	char	*value;
	char	*final;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$' && !ft_strchr("? ", str[0][i + 1])
			&& str[0][i + 1] != '\0')
		{
			var = get_var_name(&str[0][i]);
			if (ft_strcmp(var, "$_") == 0)
				value = get_last_exec_name(var + 1);
			else
				value = getenv(var + 1);
			final = replace_midstring(*str, var, value, i);
			free(*str);
			*str = final;
			free(var);
			i += ft_strlen(value) - 1;
		}
	}
}
