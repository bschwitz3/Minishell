/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:09:19 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:42:50 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list *tokens, t_list **env)
{
	char	*var;
	char	*token_str;

	if (tokens == 0)
		print_all_exported_vars(*env);
	while (tokens)
	{
		token_str = tokens->content;
		if (!has_valid_identifier_export(token_str))
			return (EXIT_FAILURE);
		if (has_only_one_cmd())
		{
			var = get_var_name(token_str);
			if (is_env_var(var, *env))
			{
				if (ft_strchr(token_str, '='))
					update_env_var_with_token(token_str, var, *env);
			}
			else
				create_environment_var(token_str, env);
			free(var);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

void	print_all_exported_vars(t_list *env)
{
	t_list	*sorted_env;
	t_list	*tmp;
	char	*env_str;
	int		i;

	sorted_env = get_sorted_env(env);
	tmp = sorted_env;
	while (tmp)
	{
		i = 0;
		env_str = (char *)tmp->content;
		if (ft_strchr(env_str, '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			while (env_str[i] != '=')
				ft_putchar_fd(env_str[i++], STDOUT_FILENO);
			printf("=\"%s\"\n", &env_str[++i]);
		}
		else
			printf("declare -x %s\n", env_str);
		tmp = tmp->next;
	}
	ft_lstclear(&sorted_env, ft_lstdel_int);
}

t_list	*get_sorted_env(t_list *env)
{
	t_list	*sorted_env;

	sorted_env = ft_lstdup(env);
	if (!sorted_env)
		quit_prog(EXIT_FAILURE);
	ft_lst_sort_str(&sorted_env, ft_strcmp);
	return (sorted_env);
}

int	has_valid_identifier_export(char *token_str)
{
	char	err_message[100];
	int		check;

	ft_bzero(err_message, 0);
	if (!is_token_valid_export(token_str, err_message))
	{
		check = 0;
		errno = ENOEXEC;
		write_msh_error(err_message);
	}
	else
		check = 1;
	return (check);
}

int	is_token_valid_export(char *token_str, char *err_message)
{
	int		check;

	if ((token_str[0] == '=')
		|| ft_isdigit(token_str[0])
		|| ft_strchr(token_str, '\'')
		|| ft_strchr(token_str, '"'))
	{
		check = 0;
		ft_strcpy(err_message, "export: `");
		ft_strcat(err_message, token_str);
		ft_strcat(err_message, "': not a valid identifier");
	}
	else
		check = 1;
	return (check);
}
