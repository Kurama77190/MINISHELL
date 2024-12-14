/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/12 09:46:59 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_double(t_data *data, char *var)
{
	t_env	*tmp;
	char	*name;
	int		i;

	i = 0;
	if (!data->env)
		return (false);
	tmp = data->env;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		return (false);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = put_value(var);
			return (free(name), true);
		}
		tmp = tmp->next;
	}
	return (free(name), false);
}

void	ft_exp_env(t_data *data)
{
	t_env	*tmp;

	if (!data || !data->env)
		return ;
	ft_sort_env(data->env);
	tmp = data->env;
	while (tmp != NULL)
	{
		if (tmp->line)
			ft_printf("declare -x %s\n", tmp->line);
		tmp = tmp->next;
	}
}

char	*ft_strjoin_empty(char const *s2)
{
	char	*str;
	char	*str_ptr;

	if (!s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	str_ptr = str;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str_ptr);
}
bool	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	ft_export(char **argv, t_data *data)
{
	int		i;
	bool	equal;
	char	*export_str;
	char	*tmp;

	i = 1;
	equal = false;
	export_str = NULL;
	if (!argv[i])
		ft_exp_env(data);
	else
	{
		while (argv[i])
		{
			if (!export_str)
				export_str = ft_strjoin_empty(argv[i]);
			else
			{
				tmp = ft_strjoin(export_str, argv[i]);
				free(export_str);
				export_str = tmp;
			}
			if (!ft_strcmp(argv[i], "="))
				equal = true;
			if (check_identifier(export_str) == false && equal == false)
			{
				ft_putstr_fd("minishell: export: `", STDERR_FILENO);
				ft_putstr_fd(argv[i], STDERR_FILENO);
				ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
				data->exit_status = 1;
				free(export_str);
				export_str = NULL;
				return ;
			}
			if (equal == true && ft_strcmp(argv[i], "="))
			{
				if (check_double(data, export_str))
					printf("check_double\n");
				else
					push_node_to_env(data, export_str);
				equal = false;
				free(export_str);
				export_str = NULL;
			}
			i++;
		}
	}
	if (export_str)
		free(export_str);
	export_str = NULL;
	data->exit_status = 0;
}
