/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:56:40 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/12 18:59:56 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Extrait la var potentielle d'une string après $
char	*get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && !is_token_delimiter(str[i]) && str[i] != '$'
		&& str[i] != '=' && !is_quote(str[i]) && str[i] != '/')
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		quit_prog(EXIT_FAILURE);
	return (var);
}

// Si le chemin de l'executable = un fichier, son nom sera remplacé
char	*get_last_exec_name(char *underscore)
{
	char	*value;
	char	*temp;

	value = getenv(underscore);
	if (is_path_executable(value))
	{
		temp = ft_strdup(ft_strrchr(value, '/') + 1);
		if (temp == 0)
			quit_prog(EXIT_FAILURE);
		free(value);
		value = temp;
		return (value);
	}
	else
		return (value);
}

// remplace les sous-chaine de char
char	*replace_midstring(char *original,
							char *old_substr,
							char *new_substr,
							int replace_i)
{
	char	*final;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(original) - ft_strlen(old_substr) + ft_strlen(new_substr);
	final = ft_calloc(len + 1, sizeof(char));
	if (final == 0)
		quit_prog(EXIT_FAILURE);
	while (*original)
	{
		if (i == replace_i)
		{
			while (new_substr && *new_substr)
				final[i++] = *(new_substr++);
			original += ft_strlen(old_substr);
			replace_i = -2;
		}
		if (*original)
			final[i++] = *(original++);
	}
	final[i] = '\0';
	return (final);
}

// remplace "$?" par l'exit_status de la dernière commande
void	replace_status_env(char **str, int last_status)
{
	int		replace_spot;
	char	*status_string;
	char	*final;

	replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	while (replace_spot != -1)
	{
		status_string = ft_itoa(last_status);
		if (status_string == 0)
			return (quit_prog(EXIT_FAILURE));
		final = replace_midstring(*str, "$?", status_string, replace_spot);
		free(status_string);
		status_string = 0;
		free(*str);
		*str = final;
		replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	}
}

// Trouve l'itération dans une sous-chaîne qui existe dans une autre string. 
int	ft_strnstr_iterator(char *haystack, char *needle, size_t len)
{
	size_t	little_len;
	int		iterator;

	iterator = 0;
	little_len = ft_strlen(needle);
	if (little_len == 0)
		return (-1);
	if (len == 0)
		return (-1);
	while (haystack[iterator] && (int)(little_len <= len - iterator))
	{
		if (!ft_strncmp(&haystack[iterator], (char *)needle, little_len))
			return (iterator);
		iterator++;
	}
	return (-1);
}
