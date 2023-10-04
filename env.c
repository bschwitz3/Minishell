/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:54:16 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 21:05:31 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// copie des variales d'env sur une liste
void	dupli_env(t_list **dup_env, char **envp)
{
	t_list	*next_env;
	int		i;
	char	*tmp;

	if (!envp || !envp[0])
		quit_prog(EXIT_FAILURE);
	i = 0;
	while (envp[i] != NULL)
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
			quit_prog(EXIT_FAILURE);
		next_env = ft_lstnew(tmp);
		if (!next_env)
			quit_prog(EXIT_FAILURE);
		ft_lstadd_back(dup_env, next_env);
		i++;
	}
}

// ajoute dernier token à variable d'env avec "_"
void	save_last_token(t_cmd_table *cmd_table)
{
	t_cmd	*last_simple_cmd;
	char	*last_token;
	char	*exec_path;

	last_simple_cmd = ft_lst_get_data_last_node(cmd_table->cmds);
	last_token = ft_lst_get_data_last_node(last_simple_cmd->tokens);
	if (last_token && has_only_one_cmd())
		exec_path = convert_to_path(last_token);
	else
	{
		exec_path = ft_strdup("");
		if (!exec_path)
			quit_prog(EXIT_FAILURE);
	}
	update_environment_var("_", exec_path, g_msh.dup_env);
	free(exec_path);
}

// si on appelle executable dans le Path, on a le chemin correspondant
char	*convert_to_path(char *token)
{
	char	*token_path;

	if (has_relative_path(token))
	{
		token_path = ft_strdup(token);
		if (!token_path)
			quit_prog(EXIT_FAILURE);
	}
	else
		token_path = get_absolute_path(token);
	return (token_path);
}

// update de l'env avec une string
void	update_environment_var(char *var, char *new_value, t_list *env)
{
	int		i;
	char	*cur_env;

	while (env)
	{
		i = 0;
		cur_env = (char *)(env->content);
		while (var[i] && cur_env[i] && (var[i] == cur_env[i]))
			i++;
		if (!var[i] && (cur_env[i] == '=' || cur_env[i] == '\0' ))
			env->content = replace_env_value(&cur_env, var, new_value);
		env = env->next;
	}
}

// joint nom de variable, "=", valeur
char	*replace_env_value(char **env_ptr, char	*var_name, char *new_value)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(var_name, "=");
	if (!temp)
		quit_prog(EXIT_FAILURE);
	final = ft_strjoin(temp, new_value);
	if (!final)
		quit_prog(EXIT_FAILURE);
	free(temp);
	temp = 0;
	free(*env_ptr);
	*env_ptr = 0;
	return (final);
}
