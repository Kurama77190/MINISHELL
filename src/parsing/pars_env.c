/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:47:08 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 08:11:29 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_env(t_data *data, char **envp)
{
	// if (!data->envp_manag.set)
	// 	return (SUCCESS);
	if (split_and_add(data, envp) == ERROR)
	{
		free_envp(data);
		free_split(data->envp_manag.env);
		ft_putstr_fd("Error: pars_env\n", 2);
		exit(2);
	}
	data->envp_manag.set = false;
	data->envp_manag.sync = true;
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

	len = (size_t)ft_lstsize_envp(data->envp_manag.envp);
	data->envp_manag.env = ft_calloc((len + 1), sizeof(char *));
	if (!data->envp_manag.env)
		return (ERROR);
	tab = data->envp_manag.env;
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
	last = data->envp_manag.envp;
	new = lst_new_envp(splited);
	if (!new)
		return (ERROR);
	if (!data->envp_manag.envp)
	{
		data->envp_manag.envp = new;
		return (SUCCESS);
	}
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
	return (SUCCESS);
}
