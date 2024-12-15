/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:29:14 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/15 00:29:23 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_heredoc(t_shell_list *node, t_data *data)
{
	t_redir	*current;
	bool	in_here_doc;

	in_here_doc = false;
	if (!node->redir)
		return (in_here_doc);
	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC)
		{
			ft_process_heredoc(current, data);
			in_here_doc = true;
		}
		current = current->next;
	}
	return (in_here_doc);
}

void	ft_read_outfile(t_shell_list *node, t_data *data)
{
	t_redir	*c;
	int		fd_out;

	c = node->redir;
	while (c)
	{
		if (c->type == OUT || c->type == D_APPEND)
		{
			if (c->value == NULL)
				ft_close_fd(data, "Error: no output file");
			if (c->type == D_APPEND)
				fd_out = open(c->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (c->type == OUT)
				fd_out = open(c->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out == -1)
				ft_close_fd(data, "Error opening fd_out");
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdout");
			close(data->fd[0]);
			close(data->fd[1]);
			close(fd_out);
		}
		c = c->next;
	}
}

void	ft_read_infile(t_shell_list *node, t_data *data)
{
	t_redir	*current;

	current = node->redir;
	while (current)
	{
		if (current->type == IN)
			ft_process_infile(current, data);
		if (current->type == D_HEREDOC)
			ft_process_heredoc_file(current, data);
		current = current->next;
	}
}

void	ft_read_redirs(t_shell_list *node, t_data *data)
{
	t_redir	*current;

	if (!node->redir)
		return ;
	current = node->redir;
	while (current)
	{
		if (current->type == IN)
			data->isinfile = true;
		if (current->type == OUT || current->type == D_APPEND)
			data->isoutfile = true;
		if (current->type == D_HEREDOC)
			data->isheredoc = true;
		current = current->next;
	}
}
