/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_redir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:34:41 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 04:03:06 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (true);
		i++;
	}
	return (false);
}

bool	is_ambiguous_redir(char *result, char **str)
{
	if (result[0] == '\0' || !is_valid_redir(result))
	{
		ft_putstr_fd("bash: ambiguous redirect\n", 2);
		free(result);
		return (true);
	}
	free(*str);
	*str = result;
	return (false);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	if (free_flag == 1 || free_flag == 3)
		free(s1);
	if (free_flag == 2 || free_flag == 3)
		free(s2);
	return (result);
}