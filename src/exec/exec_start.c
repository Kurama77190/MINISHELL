/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/22 12:41:13 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exec_builtins(t_data *data, t_token *current);
int	exec_command(t_data *data, t_token *current);

int	ft_execution(t_data *data)
{
	t_token	*current;

	current = data->token_manag.token;
	if (!current->next && !current->prev && is_builtin(current->args[0]))
	{
		exec_builtins(data, current); // secure
	}
	else
	{
		exec_command(data, current); // secure
	}
	return (SUCCESS);
}

int	exec_command(t_data *data, t_token *current)
{
	int	exit_code;

	while(current)
	{
		if(current->next)
			pipe(current->fd_pipe);
		current->pid = fork();
		if (current->pid == -1)
			ft_error(data, "Error forking\n");
		if (current->pid == 0)
		{
			if (ft_exec_redirs(current, data) == ERROR)
			{
				return (ft_free_all(data, true), exit(1), ERROR);
			}
			if (is_builtin(current->args[0]))
			{
				exit_code = ft_detect_builtin(current->args, data);
				// close(current->next->fd_pipe[1]);
				// close(current->next->fd_pipe[0]);
				ft_free_all(data, true);
				exit(exit_code);
			}
			if (ft_exec_cmd(data, current) == ERROR)
			{
				ft_free_all(data, true);
				return (ft_free_all(data, true), exit(1), ERROR);
			}
		}
		if (current->pid > 0)
			if (current->prev)
			{
				close(current->prev->fd_pipe[0]);
				close(current->prev->fd_pipe[1]);
			}
		current = current->next;
	}
	return (SUCCESS);
}

int	exec_builtins(t_data *data, t_token *current)
{
	current->builtin = true;
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO); 
	ft_exec_redirs(current, data);
	data->exit_status = ft_detect_builtin(current->args, data);
	dup2(data->stdin_backup, STDIN_FILENO);
	close(data->stdin_backup);
	dup2(data->stdout_backup, STDOUT_FILENO);
	close(data->stdout_backup);
	return (SUCCESS);
}

