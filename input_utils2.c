/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:32:12 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 19:32:39 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check si input essaie d'utilisé 
// suite : spécificité de bash qui n'est pas implémentée.
int	has_non_supported(char *input, char *test, char *err_msg)
{
	int		check;

	if (ft_strstr_quotes((char *)input, test) != 0)
	{
		check = 1;
		ft_strcpy(err_msg, "\"");
		ft_strcat(err_msg, test);
		ft_strcat(err_msg, "\" not supported");
	}
	else
		check = 0;
	return (check);
}

// has_non_supported si la la chaîne 
// suite : testée est présente séparée d'un même caractère.
int	has_non_supported_one(char *input, char *test, char *err_msg)
{
	int		check;
	char	*tmp;

	check = 0;
	tmp = (char *)input;
	while (tmp)
	{
		tmp = ft_strstr_quotes(tmp, test);
		if (tmp != 0 && *(tmp + 1) != *test)
		{
			check = 1;
			break ;
		}
		else if (tmp != 0 && *(tmp + 1) == *test)
			tmp += 2;
	}
	if (check)
	{
		ft_strcpy(err_msg, "\"");
		ft_strcat(err_msg, test);
		ft_strcat(err_msg, "\" not supported");
	}
	return (check);
}
