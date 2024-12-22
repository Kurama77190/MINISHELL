/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/22 12:23:24 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void delete_env(t_envp *tmp_env, t_envp *to_delete, t_data *data)
{
	if (tmp_env->prev)
		tmp_env->prev->next = tmp_env->next;
	else
		data->e.envp = tmp_env->next;
	if (tmp_env->next)
		tmp_env->next->prev = tmp_env->prev;
	if (to_delete->line)
		ft_free((void **)&to_delete->line);
	if (to_delete->name)
		ft_free((void **)&to_delete->name);
	if (to_delete->value)
		ft_free((void **)&to_delete->value);
	ft_free((void **)&to_delete);
}

void	search_in_env(t_data *data, char *var)
{
	t_envp	*tmp_env;
	t_envp	*to_delete;

	if (!var || !data->e.envp)
		return ;
	tmp_env = data->e.envp;
	while (tmp_env)
	{
		if (!ft_strcmp(var, tmp_env->name))
		{
			to_delete = tmp_env;
			delete_env(tmp_env, to_delete, data);
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

int	ft_unset(char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		search_in_env(data, argv[i]);
		i++;
	}
	return (0);
}
