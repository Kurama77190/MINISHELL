/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/14 22:37:19 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_commands(t_shell_list *node, t_data *data)
{
	t_shell_list	*current;
	int				i;

	i = 0;
	current = node;
	while (current)
	{
		ft_multi_pipe(current, data, i);
		current = current->next;
		i++;
	}
}

void	ft_execution(t_data *data)
{
	if (!data->shell_list || !data)
		return ;
	ft_count_levels(data->shell_list, 0, data);
	if (data->nb_levels == 0)
	{
		ft_read_heredoc(data->shell_list, data);
		ft_no_pipe(data->shell_list, data);
	}
	else if (data->nb_levels >= 1)
		ft_read_commands(data->shell_list, data);
	ft_erase_all_temp_here_doc(data->shell_list);
}
