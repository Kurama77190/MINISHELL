/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:47:08 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/19 00:55:31 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_env(t_data *data, char **envp)
{
	if (!data->envp.set)
		return (SUCCESS);
	if (split_and_add(data, envp) == ERROR)
	{
		free_lst_envp(data);
		free_split(data->envp.env);
		return (ERROR);
	}
	data->envp.set = false;
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
	char	**tab;

	len = (size_t)ft_lstsize_envp(data->envp.envp);
	data->envp.env = ft_calloc((len + 1), sizeof(char *));
	if (!data->envp.env)
		return (ERROR);
	tab = data->envp.env;
	i = 0;
	while (envp[i])
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	tab[i] = NULL;
	return (SUCCESS);
}

int	add_lst(t_data *data, char **splited)
{
	t_envp	*new;
	t_envp	*last;
	last = data->envp.envp;
	new = lst_new_envp(splited);
	if (!new)
		return (ERROR);
	if (!data->envp.envp)
	{
		data->envp.envp = new;
		return (SUCCESS);
	}
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
	return (SUCCESS);
}
