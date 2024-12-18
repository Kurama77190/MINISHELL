/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 02:10:19 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/18 02:10:35 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	current = data->token_manag.token;
	while (current)
	{
		free_redir(current);
		free_split(current->args);
		ft_free((void **)&current->command);
		tmp = current->next;
		ft_free((void **)&current);
		current = tmp;
	}
	ft_free((void **)&current);
}

void	free_redir(t_token *current)
{
	t_redir	*current_in;
	t_redir	*current_out;
	t_redir	*tmp;

	current_in = current->redir_in.head;
	current_out = current->redir_out.head;
	while (current_in)
	{
		ft_free((void **)&current_in->file_name);
		ft_free((void **)&current_in->type);
		ft_free((void **)&current_in->file_here_doc);
		tmp = current_in->next;
		ft_free((void **)&current_in);
		current_in = tmp;
	}
	while (current_out)
	{
		ft_free((void **)&current_out->file_name);
		ft_free((void **)&current_out->type);
		ft_free((void **)&current_out->file_here_doc);
		tmp = current_out->next;
		ft_free((void **)&current_out);
		current_out = tmp;
	}
}
