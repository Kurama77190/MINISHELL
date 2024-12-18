/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/18 03:46:04 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_commands(t_token *node, t_data *data)
{
	t_token	*current;
	int		i;

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
		data->stdin_backup = dup(STDIN_FILENO);
		data->stdout_backup = dup(STDOUT_FILENO);
		ft_no_pipe(data->token_manag.token, data);
		if (dup2(data->stdin_backup, STDIN_FILENO) == -1
			|| dup2(data->stdout_backup, STDOUT_FILENO) == -1)
			ft_error(data, "Error restoring stdin/stdout_backup");
		close(data->stdin_backup);
		close(data->stdout_backup);
	}
	else if (data->nb_levels >= 1)
		ft_read_commands(data->token_manag.token, data);
}
