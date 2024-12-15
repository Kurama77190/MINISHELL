/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:56:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/14 23:55:24 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_erase_all_temp_here_doc(t_shell_list *node)
{
	t_redir	*current;

	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC && current->file_here_doc != NULL)
			unlink(current->file_here_doc);
		current = current->next;
	}
}

void	ft_multi_pipe(t_shell_list *node, t_data *data, int i)
{
	pid_t	pid;

	if (i < data->nb_levels && pipe(data->pipe_fd) == -1)
		ft_error(data, "Error creating pipe");
	ft_read_heredoc(node, data);
	pid = fork();
	if (pid == -1)
		ft_error(data, "Error forking");
	if (pid == 0)
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
		if (is_builtin(node->argv[0]) == true)
		{
			ft_detect_builtin(node->argv, data);
			ft_free_all(data);
		}
		else
			exec(data, node->argv);
		exit(1);
	}
	if (i > 0)
		close(data->fd[0]);
	if (i < data->nb_levels)
	{
		data->fd[0] = data->pipe_fd[0];
		data->fd[1] = data->pipe_fd[1];
		close(data->pipe_fd[1]);
	}
	if (i == data->nb_levels)
	{
		close(data->fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	ft_no_pipe(t_shell_list *node, t_data *data)
{
	if (!node || !node->argv)
		return ;
	if (node && node->argv && is_builtin(node->argv[0]))
		ft_detect_builtin(node->argv, data);
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
			exec(data, node->argv);
			exit(1);
		}
		waitpid(node->pid, NULL, 0);
		close(data->fd[0]);
		close(data->fd[1]);
	}
}
