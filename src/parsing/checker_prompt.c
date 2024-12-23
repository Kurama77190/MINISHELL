/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:55:31 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 22:29:06 by sben-tay         ###   ########.fr       */
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
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		while (str[i] && isspace(str[i]))
			i++;
		if (str[i] == '.' && (!str[i + 1] || isspace(str[i + 1]) || str[i
				+ 1] == '/'))
		{
			ft_putendl_fd("bash: .: filename argument required", 2);
			return (true);
		}
		if (str[i] == '.' && str[i + 1] == '.' && (!str[i + 2] || isspace(str[i
					+ 2]) || str[i + 2] == '/'))
			return (ft_putendl_fd("bash: .: filename argument required", 2),
				true);
		while (str[i] && !isspace(str[i]))
			i++;
	}
	return (false);
}
