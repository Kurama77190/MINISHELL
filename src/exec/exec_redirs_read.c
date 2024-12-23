/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:29:14 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/23 22:29:06 by sben-tay         ###   ########.fr       */
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
			if (ft_process_heredoc(current, data) == ERROR)
				return (ERROR);
			in_here_doc = true;
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	ft_read_outfile(t_token *node, t_data *data)
{
	t_redir	*c;
	int		fd_o;

	(void)data;
	c = node->redir_out.head;
	while (c)
	{
		if (c->key == OUT || c->key == D_APPEND)
		{
			if (c->key == D_APPEND)
				fd_o = open(c->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (c->key == OUT)
				fd_o = open(c->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_o == -1)
			{
				perror("bash: open_out_file");
				return (ERROR);
			}
			if (dup2(fd_o, STDOUT_FILENO) == -1)
				return (ERROR);
			close(fd_o);
		}
		c = c->next;
	}
	return (SUCCESS);
}

int	ft_read_infile(t_token *node, t_data *data)
{
	t_redir	*current;

	current = node->redir_in.head;
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
	return (SUCCESS);
}
