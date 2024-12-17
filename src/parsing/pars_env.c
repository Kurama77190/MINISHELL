/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:47:08 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 10:22:10 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_env(t_data *data, char **envp)
{
	// if (!data->e.set)
	// 	return (SUCCESS);
	if (split_and_add(data, envp) == ERROR)
	{
		free_envp(data);
		free_split(data->e.env);
		ft_putstr_fd("Error: pars_env\n", 2);
		exit(2);
	}
	data->e.set = false;
	data->e.sync = true;
	return (SUCCESS);
}

int	split_and_add(t_data *data, char **envp)
{
	char	**split;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!split)
			return (ERROR);
		if (add_lst(data, split) == ERROR)
		{
			free_split(split);
			return (ERROR);
		}
		free_split(split);
		i++;
	}

	if (add_tab(data, envp) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	add_tab(t_data *data, char **envp)
{
	size_t	len;
	int		i;
	char	**tab_;

	len = (size_t)ft_lstsize_envp(data->e.envp);
	data->e.env = ft_calloc((len + 1), sizeof(char *));
	if (!data->e.env)
		return (ERROR);
	tab_ = data->e.env;
	i = 0;
	while (envp[i])
	{
		tab_[i] = ft_strdup(envp[i]);
		i++;
	}
	tab_[i] = NULL;
	return (SUCCESS);
}

int	add_lst(t_data *data, char **splited)
{
	t_envp	*new;
	t_envp	*last;
	last = data->e.envp;
	new = lst_new_envp(splited);
	if (!new)
		return (ERROR);
	if (!data->e.envp)
	{
		data->e.envp = new;
		return (SUCCESS);
	}
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
	return (SUCCESS);
}
