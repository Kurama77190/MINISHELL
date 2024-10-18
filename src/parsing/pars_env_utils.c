/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:56:36 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/18 22:20:56 by sben-tay         ###   ########.fr       */
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
	t_envp *current;
	t_envp *next;

	current = data->envp.envp;
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
	data->envp.envp = NULL;
}

