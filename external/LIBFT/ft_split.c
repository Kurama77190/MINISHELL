/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 04:07:16 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/15 00:22:30 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*ft_strndup_split(const char *s1, int index, int n)
{
	int		i;
	char	*dup;

	dup = malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s1[index];
		i++;
		index++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_free_split(char **res, int index)
{
	while (index >= 0)
	{
		free(res[index]);
		index--;
	}
	free(res);
}

static bool	ft_processwords(char const *s, char c, char **res, int words)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		n = 0;
		while (s[i + n] && s[i + n] != c)
			n++;
		res[j] = ft_strndup_split(s, i, n);
		if (!res[j])
			return (ft_free_split(res, j), false);
		j++;
		i += n;
	}
	return (res[j] = NULL, true);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**res;

	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	if (ft_processwords(s, c, res, words) == false)
		return (NULL);
	return (res);
}
