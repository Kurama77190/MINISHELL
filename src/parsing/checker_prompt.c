/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:55:31 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 06:34:40 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valided(char *str);

int	check_cmd(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(data->prompt.read_line);
	if (!str)
		return (ERROR);
	if (!is_valided(str))
	{
		free(str);
		return (ERROR);
	}
	return (SUCCESS);
}

static bool	is_valided(char *str)
{
	if (!check_redirection(str))
	{
		return (false);
	}
	if (!check_pipe(str))
	{
		return (false);
	}
	if (is_empty_prompt(str))
	{
		return (false);
	}
	return (true);
}
