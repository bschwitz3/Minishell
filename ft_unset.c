/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:34:56 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:18:36 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_list *tokens, t_list **env)
{
	char	*token_str;

	while (tokens)
	{
		token_str = tokens->content;
		if (!has_valid_identifier_unset(token_str))
			return (EXIT_FAILURE);
		if (has_only_one_cmd())
		{	
			if (is_env_var(token_str, *env))
				delete_env_var(token_str, env);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

void	delete_env_var(char *var, t_list **env)
{
	t_list	*env_ptr;
	int		i;
	char	*cur_env;
	int		env_index;

	env_ptr = *env;
	env_index = 0;
	while (env_ptr)
	{
		i = 0;
		cur_env = (char *)(env_ptr->content);
		while (var[i] && cur_env[i] && (var[i] == cur_env[i]))
			i++;
		if (!var[i] && (cur_env[i] == '=' || cur_env[i] == '\0' ))
		{
			ft_lstdel_node_nbr(env, env_index, ft_delete_list_str);
			return ;
		}
		env_index++;
		env_ptr = env_ptr->next;
	}
}

int	has_valid_identifier_unset(char *token_str)
{
	char	err_message[100];
	int		check;

	ft_bzero(err_message, 0);
	if (!is_token_valid_unset(token_str, err_message))
	{
		check = 0;
		errno = ENOEXEC;
		write_msh_error(err_message);
	}
	else
		check = 1;
	return (check);
}

int	is_token_valid_unset(char *token_str, char *err_message)
{
	int		check;

	if (token_str == 0)
		return (1);
	if (ft_strchr(token_str, '=')
		|| ft_strchr(token_str, '\'')
		|| ft_strchr(token_str, '"')
		|| ft_strchr(token_str, '$')
		|| *token_str == '/'
		|| ft_isdigit(*token_str))
	{
		check = 0;
		ft_strcpy(err_message, "unset: `");
		ft_strcat(err_message, token_str);
		ft_strcat(err_message, "': not a valid identifier");
	}
	else
		check = 1;
	return (check);
}

void	ft_lstdel_node_nbr(t_list **lst, int node_nbr, void (*del)(void*))
{
	if (!lst)
		return ;
	if (node_nbr == 0)
		ft_lstdel_first(lst, del);
	else if (node_nbr == ft_lstsize(*lst) - 1)
		ft_lstdel_last(*lst, del);
	else if (node_nbr >= ft_lstsize(*lst))
		return ;
	else
		ft_lstdel_middle(lst, node_nbr, del);
	return ;
}
