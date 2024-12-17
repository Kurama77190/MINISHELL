/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 18:35:28 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_commands(t_token *node, t_data *data)
{
	t_token	*current;
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
	if (!data->token_manag.token || !data || !data->token_manag.token->args)
		return ;
	ft_count_levels(data->token_manag.token, 0, data);
	if (data->nb_levels == 0)
	{
		ft_read_heredoc(data->token_manag.token->redir_in.head, data);
		ft_no_pipe(data->token_manag.token, data);
	}
	else if (data->nb_levels >= 1)
		ft_read_commands(data->token_manag.token, data);
	//ft_erase_all_temp_here_doc(data->shell_list);
}
