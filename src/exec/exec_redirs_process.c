/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:26 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/19 17:43:19 by sben-tay         ###   ########.fr       */
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
		return (ERROR);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		perror("bash: dup2 infile: ");
		return (ERROR);
	}
	close(fd_in);
}

int	ft_process_heredoc_file(t_redir *current, t_data *data)
{
	int	fd_in;

	if (current->file_here_doc == NULL)
	{
		perror("bash: no here_doc detected: ");
		return (ERROR);
	}
	fd_in = open(current->file_here_doc, O_RDONLY);
	if (fd_in == -1)
	{
		perror("bash: open here_doc: ");
		return (ERROR);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		perror("bash: errror set stdin here_doc: ");
		return (ERROR);
	}
	close(fd_in);
}

int	ft_exec_redirs(t_token *node, t_data *data)
{
	if (!node->redir_in.head || !node->redir_out.head)
		return ;
	if (node->next)
	{
		close(node->fd_pipe[0]);
		dup2(node->fd_pipe[1], STDIN_FILENO);
		close(node->fd_pipe[1]);
	}
	if (node->prev)
	{
		close(node->fd_pipe[1]);
		dup2(node->fd_pipe[0], STDOUT_FILENO);
		close(node->fd_pipe[0]);
	}
	if (node->redir_in.head)
	{
		if (ft_read_infile(node->redir_in.head, data) == ERROR)
			return (ERROR);
	}
	if (node->redir_out.head)
	{
		if (ft_read_outfile(node->redir_out.head, data) == ERROR)
			return (ERROR);
	}
}
