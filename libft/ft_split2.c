/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:00:38 by bschwitz          #+#    #+#             */
/*   Updated: 2022/11/30 16:02:05 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	find_length(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (!ft_strchr(charset, *str++))
			count++;
	}
	return (count);
}

static void	import_str(char **dest, char *src, int start, int end)
{
	*dest = malloc(((end - start + 1) * sizeof(char)));
	if (!(*dest))
		return ;
	ft_strncpy(*dest, src, end - start);
	(*dest)[end - start] = '\0';
}

char	**ft_split2(char *str, char *charset)
{
	char	**strs;
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (str == 0)
		return (0);
	strs = malloc((find_length(str, charset) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (str[j] != '\0')
	{
		i = j;
		while (!ft_strchr(charset, str[j]) && str[j] != '\0')
			j++;
		if (i != j)
			import_str(&strs[k++], &str[i], i, j);
		else
			j++;
	}
	strs[k] = 0;
	return (strs);
}
