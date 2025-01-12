/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/24 08:49:44 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(t_envp *node, t_data *data)
{
	if (!node || !data)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		data->e.envp = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node->line)
		ft_free((void **)&node->line);
	if (node->name)
		ft_free((void **)&node->name);
	if (node->value)
		ft_free((void **)&node->value);
	ft_free((void **)&node);
}

void	search_in_env(t_data *data, char *var)
{
	t_envp	*current;

	if (!var || !data->e.envp)
		return ;
	current = data->e.envp;
	while (current)
	{
		if (current->name && !ft_strcmp(var, current->name))
		{
			delete_env(current, data);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(char **argv, t_data *data)
{
	int	i;

	if (!argv || !data)
		return (1);
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			search_in_env(data, argv[i]);
		i++;
	}
	return (0);
}
