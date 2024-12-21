/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:26 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/21 12:17:03 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_infile(t_redir *current, t_data *data)
{
	int	fd_in;

	fd_in = open(current->file_name, O_RDONLY);
	if (fd_in == -1)
	{
		perror("bash :open infile: ");
		ft_free_all(data, true);
		return (ERROR);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		perror("bash: dup2 infile: ");
		ft_free_all(data, true);
		return (ERROR);
	}
	close(fd_in);
	return (SUCCESS);
}

int	ft_process_heredoc_file(t_redir *current, t_data *data)
{
	int	fd_in;

	if (current->file_here_doc == NULL)
	{
		perror("bash: no here_doc detected: ");
		ft_free_all(data, true);
		return (ERROR);
	}
	fd_in = open(current->file_here_doc, O_RDONLY);
	if (fd_in == -1)
	{
		perror("bash: open here_doc: ");
		ft_free_all(data, true);
		return (ERROR);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		ft_free_all(data, true);
		perror("bash: errror set stdin here_doc: ");
		return (ERROR);
	}
	close(fd_in);
	return (SUCCESS);
}

int	ft_exec_redirs(t_token *node, t_data *data)
{
	if (node->next)
	{
		close(node->fd_pipe[0]);
		dup2(node->fd_pipe[1], STDOUT_FILENO);
		close(node->fd_pipe[1]);
	}
	if (node->prev)
	{
		close(node->prev->fd_pipe[1]);
		dup2(node->prev->fd_pipe[0], STDIN_FILENO);
		close(node->prev->fd_pipe[0]);
	}
	if (ft_read_infile(node, data) == ERROR)
		return (ERROR);
	if (ft_read_outfile(node, data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
