/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:01:07 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/13 02:28:42 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_builtin_1(t_data *data, char *token, t_token **new)
{
	(void)data;
	if (ft_strncmp(token, "echo", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strncmp(token, "cd", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strncmp(token, "pwd", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	return (SUCCESS);
}

int	is_builtin_2(t_data *data, char *token, t_token **new)
{
	(void)data;
	if (ft_strncmp(token, "export", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strncmp(token, "unset", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strncmp(token, "env", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	return (SUCCESS);
}

int	is_builtin_3(t_data *data, char *token, t_token **new)
{
	(void)data;
	if (ft_strncmp(token, "exit", ft_strlen(token)) == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	return (SUCCESS);
}

int	is_args(t_data *data, char *token, t_token **new)
{
	(void)data;
	char	**tmp;

	if (!(*new)->args)
	{
		tmp = ft_split(token, ' ');
		if (!tmp)
			return (ERROR);
		(*new)->args = tmp;
	}
	else
	{
		tmp = ft_split(token, ' ');
		if (!tmp)
			return (ERROR);
	}
	return (SUCCESS);
}

int	is_command(t_data *data, char *token, t_token **new)
{
	(void)data;
	(*new)->command = ft_strdup(token);
	if (!(*new)->command)
		return (ERROR);
	return (SUCCESS);
}
