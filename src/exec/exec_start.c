/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/21 09:51:28 by samy             ###   ########.fr       */
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
		ft_multi_pipe(current, data);
		current = current->next;
		i++;
	}
}

int	ft_execution(t_data *data)
{
	if (!data->token_manag.token || !data->token_manag.token->args)
		return (ERROR);
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	if (data->token_manag.token->next == NULL)
	{
		ft_read_heredoc(data->token_manag.token->redir_in.head, data);
		ft_no_pipe(data->token_manag.token, data);
	}
	else
		ft_read_commands(data->token_manag.token, data);
	dup2(data->stdin_backup, STDIN_FILENO);
	close(data->stdin_backup);
	dup2(data->stdout_backup, STDOUT_FILENO);
	close(data->stdout_backup);
	return (SUCCESS);
}
