/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:55:31 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/21 05:01:14 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valided(char *str, int *exit_status);

int	check_cmd(t_data *data)
{
	char	*str;

	str = ft_strdup(data->prompt.read_line);
	if (!str)
		return (ERROR);
	if (!is_valided(str, &data->exit_status))
	{
		free(str);
		return (ERROR);
	}
	ft_free((void **)&str);
	return (SUCCESS);
}

static bool	is_valided(char *str, int *exit_status)
{
	if (!check_redirection(str))
	{
		*exit_status = 2;
		return (false);
	}
	if (!check_pipe(str))
	{
		*exit_status = 2;
		return (false);
	}
	if (!check_unclosed_quotes(str))
	{
		*exit_status = 2;
		return (false);
	}
	if (is_empty_prompt(str))
	{
		*exit_status = 0;
		return (false);
	}
	return (true);
}
