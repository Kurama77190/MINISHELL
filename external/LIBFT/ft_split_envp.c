/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:45:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/21 05:40:12 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nombremot(char *str, char c);
static int	ft_lenmot(char *str, char c);
static char	**ft_malloc_error(char **tab);
static bool	ft_ajoutdesmots(char **tab, char *str, int i, char c);

char	**ft_split_envp(char const *s, char c)
{
	char	*str;
	char	**tab;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	tab = malloc(sizeof(char *) * (ft_nombremot(str, c) + 1));
	if (!tab)
		return (NULL);
	if (!ft_ajoutdesmots(tab, str, i, c))
	{
		ft_malloc_error(tab);
		return (NULL);
	}
	return (tab);
}

static int	ft_nombremot(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static int	ft_lenmot(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i + 1);
}

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static bool	ft_ajoutdesmots(char **tab, char *str, int i, char c)
{
	int	j;
	int	k;

	j = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] == c)
			i++;
		if (str[i])
		{
			tab[j] = malloc((sizeof(char)) * (ft_lenmot(str + i, c) + 2));
			if (!tab[j])
				return (false);
			while (str[i] && str[i] != c)
			{
				tab[j][k++] = str[i++];
			}
			tab[j][k++] = '/';
			tab[j][k] = '\0';
			j++;
		}
	}
	tab[j] = NULL;
	return (true);
}
