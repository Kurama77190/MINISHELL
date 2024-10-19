/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:03:45 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/19 16:06:50 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nombremot(char *str);
static int	ft_lenmot(char *str);
static char	**ft_malloc_error(char **tab);
bool		ft_ajoutdesmots(char **tab, char *str, int i);

char	**split_token(char const *s)
{
	char	*str;
	char	**tab;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	tab = malloc(sizeof(char *) * (ft_nombremot(str) + 1));
	if (!tab)
		return (NULL);
	if (!ft_ajoutdesmots(tab, str, i))
	{
		ft_malloc_error(tab);
		return (NULL);
	}
	return (tab);
}

static int	ft_nombremot(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_redir(str[i]) && str[i])
			i++;
		if (str[i])
			count++;
		while (!is_redir(str[i]) && str[i])
			i++;
	}
	return (count);
}

static int	ft_lenmot(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_redir(str[i]))
		i++;
	return (i);
}

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

bool	ft_ajoutdesmots(char **tab, char *str, int i)
{
	int	j;
	int	k;

	j = 0;
	while (str[i])
	{
		k = 0;
		while (is_redir(str[i]))
			i++;
		if (str[i])
		{
			tab[j] = malloc((sizeof(char)) * (ft_lenmot(str + i) + 1));
			if (!tab[j])
				return (false);
			while (str[i] && !is_redir(str[i]))
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			tab[j++][k] = '\0';
		}
	}
	tab[j] = NULL;
	return (true);
}
