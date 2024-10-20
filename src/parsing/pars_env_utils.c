/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:56:36 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/19 03:33:31 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_envp(t_envp *lst)
{
	size_t	i;
	t_envp	*tmp;

	tmp = lst;
	i = 0;
	if (tmp == NULL)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_envp	*lst_new_envp(char **splited)
{
	t_envp	*new;

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strjoin(splited[0], "=");
	if (!new->name)
	{
		ft_free((void **)&new);
		return (NULL);
	}
	new->value = ft_strdup(splited[1]);
	if (!new->value)
	{
		ft_free((void **)&new->name);
		ft_free((void **)&new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	free_lst_envp(t_data *data)
{
	t_envp	*current;
	t_envp	*next;

	current = data->envp_manag.envp;
	if (!current)
		return ;
	while (current->next)
	{
		ft_free((void **)&current->name);
		ft_free((void **)&current->value);
		next = current->next;
		ft_free((void **)&current);
		current = next;
	}
	data->envp_manag.envp = NULL;
}

int	uptdate_env(t_data *data)
{
	size_t	len;
	size_t	i;
	t_envp	*tmp;

	ft_free((void **)data->envp_manag.env);
	len = ft_lstsize_envp(data->envp_manag.envp);
	data->envp_manag.env = ft_calloc((len + 1), sizeof(char *));
	if (!data->envp_manag.env)
		return (ERROR);
	i = 0;
	tmp = data->envp_manag.envp;
	while (data->envp_manag.envp)
	{
		data->envp_manag.env[i] = ft_strjoin(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	data->envp_manag.env[i] = NULL;
	data->envp_manag.sync = true;
	return (SUCCESS);
}
