/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:29:14 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/19 17:42:15 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_heredoc(t_redir *node, t_data *data)
{
	t_redir	*current;
	bool	in_here_doc;

	in_here_doc = false;
	if (!node)
		return (in_here_doc);
	current = node;
	while (current)
	{
		if (current->key == D_HEREDOC)
		{
			ft_process_heredoc(current, data);
			in_here_doc = true;
		}
		current = current->next;
	}
	return (in_here_doc);
}

void	ft_read_outfile(t_redir *node, t_data *data)
{
	t_redir	*c;
	int		fd_o;

	c = node;
	while (c)
	{
		if (c->key == OUT || c->key == D_APPEND)
		{
			if (c->key == D_APPEND)
				fd_o = open(c->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (c->key == OUT)
				fd_o = open(c->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_o == -1)
				ft_close_fd(data, "Error opening fd_out");
			if (dup2(fd_o, STDOUT_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdout");
			close(fd_o);
		}
		c = c->next;
	}
}

int	ft_read_infile(t_redir *node, t_data *data)
{
	t_redir	*current;

	current = node;
	while (current)
	{
		if (current->key == IN)
		{
			if (ft_process_infile(current, data) == ERROR)
				return (ERROR);
			
		}
		if (current->key == D_HEREDOC)
			ft_process_heredoc_file(current, data);
		current = current->next;
	}
}
