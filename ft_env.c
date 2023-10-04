/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snadji-h <snadji-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:25:36 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 14:01:47 by snadji-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	char	*env_str;

	save_last_token(g_msh.curr_cmd_table);
	while (env)
	{
		env_str = (char *)env->content;
		if (ft_strchr(env_str, '='))
			printf("%s\n", env_str);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
