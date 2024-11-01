/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:01:07 by sben-tay          #+#    #+#             */
/*   Updated: 2024/11/01 06:05:57 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_builtin_1(t_data *data, char *token, t_token **new)
{
	if (ft_strcmp(token, "echo") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strcmp(token, "cd") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strcmp(token, "pwd") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	else
		return (SUCCESS);
}

int	is_builtin_2(t_data *data, char *token, t_token **new)
{
	if (ft_strcmp(token, "export") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strcmp(token, "unset") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	if (ft_strcmp(token, "env") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	else
		return (SUCCESS);
}

int	is_builtin_3(t_data *data, char *token, t_token **new)
{
	if (ft_strcmp(token, "exit") == 0)
	{
		(*new)->command = ft_strdup(token);
		if (!(*new)->command)
			return (ERROR);
		(*new)->builtin = 1;
	}
	else
		return (SUCCESS);
}

int	is_args(t_data *data, char *token, t_token **new)
{
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
	(*new)->command = ft_strdup(token);
	if (!(*new)->command)
		return (ERROR);
	return (SUCCESS);
}
