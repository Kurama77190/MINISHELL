/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:26 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/15 00:29:57 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_infile(t_redir *current, t_data *data)
{
	int	fd_in;

	fd_in = open(current->value, O_RDONLY);
	if (fd_in == -1)
	{
		ft_error(data, "Error opening input file");
		return ;
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		ft_error(data, "Error redirecting stdin");
		return ;
	}
	close(fd_in);
}

void	ft_process_heredoc_file(t_redir *current, t_data *data)
{
	int	fd_in;

	if (current->file_here_doc == NULL)
	{
		ft_error(data, "Error: no file here doc");
		return ;
	}
	fd_in = open(current->file_here_doc, O_RDONLY);
	if (fd_in == -1)
	{
		ft_error(data, "Error opening heredoc file");
		return ;
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		ft_error(data, "Error redirecting stdin");
		return ;
	}
	close(fd_in);
}

void	ft_exec_redirs(t_shell_list *node, t_data *data)
{
	if (!node->redir)
		return ;
	ft_read_infile(node, data);
	ft_read_outfile(node, data);
}
