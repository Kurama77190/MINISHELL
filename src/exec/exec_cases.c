/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:56:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/23 11:04:23 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ft_erase_all_temp_here_doc(t_redir *node)
{
	t_redir	*current;

	current = node;
	while (current)
	{
		if (current->key == D_HEREDOC && current->file_here_doc != NULL)
		{
			unlink(current->file_here_doc);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	ft_multi_pipe_child(t_token *node, t_data *data)
{
	if (node->args)
	{
		if (is_builtin(node->args[0]))
		{
			ft_detect_builtin(node->args, data);
			ft_free_all(data, true);
			exit(data->exit_status);
		}
		else
		{
			if (ft_exec_cmd(data, node) == ERROR)
			{
				ft_free_all(data, true);
				exit(1);
			}
		}
	}
	return (SUCCESS);
}

int	ft_multi_pipe(t_token *node, t_data *data)
{
	pipe(node->fd_pipe);
	node->pid = fork();
	if (node->pid == -1)
		ft_error(data, "Error forking");
	if (node->pid == 0)
	{
		ft_exec_redirs(node, data);
		ft_multi_pipe_child(node, data);
	}
	return (SUCCESS);
}

int	ft_no_pipe(t_token *node, t_data *data)
{
	if (node && node->args && is_builtin(node->args[0]))
	{
		data->stdin_backup = dup(STDIN_FILENO);
		data->stdout_backup = dup(STDOUT_FILENO);
		ft_exec_redirs(node, data);
		ft_detect_builtin(node->args, data);
		dup2(data->stdin_backup, STDIN_FILENO);
		close(data->stdin_backup);
		dup2(data->stdout_backup, STDOUT_FILENO);
		close(data->stdout_backup);
		// node->builtin = true;
	}
	else
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking\n");
		if (node->pid == 0)
		{
			if (ft_exec_redirs(node, data) == ERROR)
			{
				return (ft_free_all(data, true), exit(1), ERROR);
			}
			if (ft_exec_cmd(data, node) == ERROR)
			{
				ft_free_all(data, true);
				return (ft_free_all(data, true), exit(1), ERROR);
			}
		}
	}
	return (SUCCESS);
}
