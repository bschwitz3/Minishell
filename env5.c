/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:00:33 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:03:13 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// joins des liste de string en une string
char	*join_split_token(t_list *split_token)
{
	char	*token;
	int		new_token_size;

	new_token_size = get_new_token_size(split_token);
	token = ft_calloc(new_token_size + 1, sizeof(char));
	if (!token)
		quit_prog(EXIT_FAILURE);
	while (split_token)
	{
		ft_strcat(token, (char *)split_token->content);
		split_token = split_token->next;
	}
	ft_lstclear(&split_token, free);
	return (token);
}

// taille cumulée de toute la liste
int	get_new_token_size(t_list *split_token)
{
	int		size;
	char	*token;

	size = 0;
	while (split_token)
	{
		token = split_token->content;
		size += ft_strlen(token);
		split_token = split_token->next;
	}
	return (size);
}

// verifie si token est vide
int	is_token_empty(void *data)
{
	int		check;
	char	*token;

	token = data;
	if (*token == '\0')
		check = 1;
	else
		check = 0;
	return (check);
}

// check si le nom de la var d'env est utilisée
int	is_env_var(char *potential_var, t_list *env)
{
	int		i;
	char	*env_str;

	while (env)
	{
		i = 0;
		env_str = (char *)env->content;
		while (potential_var[i] && env_str[i]
			&& (potential_var[i] == env_str[i]))
			i++;
		if ((potential_var[i] == 0 || ft_isspace(potential_var[i]))
			&& (env_str[i] == '=' || env_str[i] == '\0'))
			return (1);
		env = env->next;
	}
	return (0);
}

// cette variable ne doit pas être initialisée au depart
void	unset_oldpwd(void)
{
	if (is_env_var("OLDPWD", g_msh.dup_env) == 0)
		create_environment_var("OLDPWD", &g_msh.dup_env);
	else
		remove_env_value("OLDPWD");
}
