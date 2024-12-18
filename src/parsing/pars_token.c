/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:00:51 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/18 02:12:36 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		identifier_token(t_data *data, char *token);

int	pars_token(t_data *data)
{
	int	i;

	data->token_manag.line = ft_strtrim(data->prompt.read_line, " ");
	if (!data->token_manag.line)
		return (ERROR);
	data->token_manag.readed = split_pipes_secure(data->token_manag.line);
	if (!data->token_manag.readed)
		return (ft_free((void **)&data->token_manag.line), ERROR);
	i = 0;
	while (data->token_manag.readed[i])
	{
		if (setup_token(data, data->token_manag.readed[i]) == ERROR)
			return (free_split(data->token_manag.readed),
				ft_free((void **)&data->token_manag.line), ERROR);
		i++;
	}
	ft_free((void **)&data->token_manag.line);
	free_split(data->token_manag.readed);
	return (SUCCESS);
}

int	setup_token(t_data *data, char *token)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (ERROR);
	if (setup_redir(token, new) == ERROR)
	{
		free_redir(new);
		ft_free((void **)&new);
		return (ERROR);
	}
	if (setup_cmd(token, new) == ERROR)
	{
		free_redir(new);
		ft_free((void **)&new);
		return (ERROR);
	}
	add_back_token(data, new);
	return (SUCCESS);
}

int	add_back_token(t_data *data, t_token *new)
{
	t_token	*current;

	if (!data->token_manag.token)
	{
		data->token_manag.token = new;
		return (SUCCESS);
	}
	current = data->token_manag.token;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (SUCCESS);
}
