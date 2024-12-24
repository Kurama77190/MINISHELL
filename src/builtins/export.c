/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/24 03:51:42 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_double(t_data *data, char *var)
{
	t_envp	*tmp;
	char	*name;
	int		i;

	i = 0;
	tmp = data->e.envp;
	if (!tmp)
		return (false);
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		return (false);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			ft_free((void **)&tmp->value);
			tmp->value = put_value(var);
			return (ft_free((void **)&name), true);
		}
		tmp = tmp->next;
	}
	return (ft_free((void **)&name), false);
}

void	ft_exp_env(t_data *data)
{
	t_envp	*tmp;

	if (!data || !data->e.envp)
		return ;
	ft_sort_env(data->e.envp);
	tmp = data->e.envp;
	while (tmp != NULL)
	{
		if (tmp->line)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->line, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

bool	check_ifvalue(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	check_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-')
			return (false);
		i++;
	}
	i = 0;
	if (ft_isdigit(str[0]) || ft_is_operator(str[0]) || ft_is_separator(str))
		return (false);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
				return (false);
			if (ft_isdigit(str[i - 1]) || ft_is_operator(str[i - 1]))
				return (false);
			return (true);
		}
		i++;
	}
	return (true);
}

int	ft_export(char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (!argv[i])
		ft_exp_env(data);
	else
	{
		while (argv[i])
		{
			if (check_valid_identifier(argv[i]) == false)
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				return (1);
			}
			if (check_ifvalue(argv[i]) == true && check_double(data,
					argv[i]) == false)
				push_node_to_env(data, argv[i]);
			i++;
		}
	}
	return (0);
}
