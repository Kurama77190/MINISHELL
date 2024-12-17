/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:28:14 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 21:23:26 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_env_lines(t_envp *a, t_envp *b)
{
	char	*temp;

	temp = a->line;
	a->line = b->line;
	b->line = temp;
}

void	ft_sort_env(t_envp *env)
{
	t_envp	*tmp;
	bool	is_sort;

	is_sort = false;
	while (is_sort == false)
	{
		is_sort = true;
		tmp = env;
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->line, tmp->next->line) > 0)
			{
				ft_swap_env_lines(tmp, tmp->next);
				is_sort = false;
			}
			tmp = tmp->next;
		}
	}
}
