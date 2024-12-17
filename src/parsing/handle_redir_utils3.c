/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:15:22 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 03:00:33 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_type(char	*str, t_redir	**new)
{
	int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			(*new)->key = D_HEREDOC;
		else
			(*new)->key = IN;
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			(*new)->key = D_APPEND;
		else
			(*new)->key = OUT;
	}
}

t_redir	*new_redir_in(char *token)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = infile_name(token);
	if (!new->file_name)
		return (free(new), new = NULL, NULL);
	new->type = infile_type(token);
	if (!new->file_name)
		return (free(new), new = NULL, NULL);
	set_type(new->type, &new);
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
	set_type(new->type, &new);
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
