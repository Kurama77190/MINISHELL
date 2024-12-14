/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:42:18 by samy              #+#    #+#             */
/*   Updated: 2024/12/14 03:37:08 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redir(t_data *data, char *token, t_token *new)
{
	// t_redir_manag	redir_in;
	// t_redir_manag	redir_out;

	// new->redir_in = ft_calloc(1, sizeof(t_redir_manag));
	// if (!new->redir_in)
	// 	return (ERROR);
	// new->redir_out = ft_calloc(1, sizeof(t_redir_manag));
	// if (!new->redir_out)
	// {
	// 	ft_free((void **)&new->redir_in);
	// 	return (ERROR);
	// }
	
	
	while (ft_strchr(token, '>') != NULL || ft_strchr(token, '<') != NULL)
	{
		// redir_in = new->redir_in;
		// redir_out = new->redir_out;
		if (add_redir_in(data, token, &new->redir_in == ERROR)
			return (ERROR);
		if (add_redir_out(data, token, &redir_out))
			return (ERROR);
	}
	return (SUCCESS);
}

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

int	add_redir_out(t_data *data, char *token, t_redir_manag *param)
{
	t_redir	*new;
	t_redir	*tmp;

	(void)data;
	new = new_redir_out(token);
	if (!new)
		return (ERROR);
	if (param->head == NULL)
	{
		param->head = new;
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
	}
	return (SUCCESS);
}
