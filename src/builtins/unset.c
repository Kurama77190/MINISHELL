/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 19:31:07 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_in_env(t_data *data, char *var)
{
	t_envp	*tmp_env;

	tmp_env = data->e.envp;
	while (tmp_env)
	{
		if (!ft_strcmp(var, tmp_env->name))
		{
			if (tmp_env->line)
				ft_free((void **)&tmp_env->line);
			if (tmp_env->name)
				ft_free((void **)&tmp_env->name);
			if (tmp_env->value)
				ft_free((void **)&tmp_env->value);
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

void	ft_unset(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		search_in_env(data, argv[i]);
		i++;
	}
	data->exit_status = 0;
}
