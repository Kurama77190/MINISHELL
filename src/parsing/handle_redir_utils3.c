/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:15:22 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/15 02:21:20 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir_in(char *token)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = infile_name(token);
	if (!new->file_name)
		return (NULL);
	new->type = infile_type(token);
	if (!new->file_name)
		return (NULL);
	return (new);
}

t_redir	*new_redir_out(char *token)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = outfile_name(token);
	if (!new->file_name)
		return (NULL);
	new->type = outfile_type(token);
	if (!new->file_name)
		return (NULL);
	return (new);
}

int	add_redir_in(char *token, t_redir_manag *param)
{
	t_redir	*new;
	t_redir	*tmp;

	new = new_redir_in(token);
	if (!new)
		return (ERROR);
	if (param->head == NULL)
	{
		param->head = new;
		param->current = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = param->current;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
		param->current = new;
	}
	return (SUCCESS);
}

int	add_redir_out(char *token, t_redir_manag *param)
{
	t_redir	*new;
	t_redir	*tmp;

	new = new_redir_out(token);
	if (!new)
		return (ERROR);
	if (param->head == NULL)
	{
		param->head = new;
		param->current = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = param->head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (SUCCESS);
}
