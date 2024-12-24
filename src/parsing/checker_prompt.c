/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:55:31 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 04:06:50 by rbalazs          ###   ########.fr       */
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

bool		is_solo_duo_point(char *str);

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
		return (false);
	}
	return (true);
}

bool	is_solo_duo_point(char *str)
{
	char	*trimmed;

	if (!str)
		return (false);
	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	if (!trimmed)
		return (false);
	if (ft_strcmp(trimmed, ".") == 0
		|| ft_strcmp(trimmed, "..") == 0
		|| ft_strcmp(trimmed, "./") == 0
		|| ft_strcmp(trimmed, "../") == 0)
	{
		ft_putendl_fd("bash: .: filename argument required", 2);
		free(trimmed);
		return (true);
	}
	if ((ft_strncmp(trimmed, "./", 2) == 0 && ft_strlen(trimmed) > 2)
		|| (ft_strncmp(trimmed, "../", 3) == 0 && ft_strlen(trimmed) > 3))
	{
		free(trimmed);
		return (false);
	}
	free(trimmed);
	return (false);
}
