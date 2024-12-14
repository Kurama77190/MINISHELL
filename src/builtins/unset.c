/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/14 13:04:05 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_in_env(t_data *data, char *var)
{
	t_env	*tmp_env;

	tmp_env = data->env;
	while (tmp_env)
	{
		if (!ft_strcmp(var, tmp_env->name))
		{
			if (tmp_env->line)
				free(tmp_env->line);
			tmp_env->line = NULL;
			if (tmp_env->name)
				free(tmp_env->name);
			tmp_env->name = NULL;
			if (tmp_env->value)
				free(tmp_env->value);
			tmp_env->value = NULL;
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
