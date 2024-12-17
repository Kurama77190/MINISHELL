/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:56:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 23:04:19 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_erase_all_temp_here_doc(t_redir *node)
{
	t_redir	*current;

	current = node;
	while (current)
	{
		if (current->key == D_HEREDOC && current->file_here_doc != NULL)
			unlink(current->file_here_doc);
		current = current->next;
	}
}

void	ft_multi_pipe_child(t_token *node, t_data *data, int i)
{
	if (i > 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
	}
	if (i < data->nb_levels)
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
	close(data->pipe_fd[0]);
	ft_exec_redirs(node, data);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	if (node->args)
	{
		if (is_builtin(node->args[0]) == true)
		{
			ft_detect_builtin(node->args, data);
			ft_free_all(data, true);
		}
		else
			exec(data, node->args);
	}
	ft_free_all(data, true);
	exit(1);
}

void	ft_multi_pipe(t_token *node, t_data *data, int i)
{
	if (i < data->nb_levels && pipe(data->pipe_fd) == -1)
		ft_error(data, "Error creating pipe");
	// ft_read_heredoc(node, data);
	node->pid = fork();
	if (node->pid == -1)
		ft_error(data, "Error forking");
	if (node->pid == 0)
		ft_multi_pipe_child(node, data, i);
	if (i > 0)
		close(data->fd[0]);
	if (i < data->nb_levels)
	{
		data->fd[0] = data->pipe_fd[0];
		data->fd[1] = data->pipe_fd[1];
		close(data->pipe_fd[1]);
	}
	//i == data->nb_levels
	if (1)
	{
		close(data->fd[0]);
		waitpid(node->pid, NULL, 0);
	}
	// ft_erase_all_temp_here_doc(node);
}


void	ft_no_pipe(t_token *node, t_data *data)
{
	if (node && node->args && is_builtin(node->args[0]))
	{
		ft_exec_redirs(node, data);
		ft_detect_builtin(node->args, data);
	}
	else
	{
		if (pipe(data->fd) == -1)
			ft_error(data, "Error creating pipe");
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			ft_exec_redirs(node, data);
			close(data->fd[0]);
			close(data->fd[1]);
			exec(data, node->args);
			ft_free_all(data, true);
			exit(1);
		}
		waitpid(node->pid, NULL, 0);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	ft_erase_all_temp_here_doc(node->redir_in.head);
}
