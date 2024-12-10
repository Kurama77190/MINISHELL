/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:42:18 by samy              #+#    #+#             */
/*   Updated: 2024/12/07 03:06:25 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	setup_redir(t_data *data, char *token, t_token *new)
{
	(*new).redir_in = ft_calloc(1, sizeof(t_redir));
	if (!(*new).redir_in)
		return (ERROR);
	(*new).redir_out = ft_calloc(1, sizeof(t_redir));
	if (!(*new).redir_out)
	{
		ft_free(&(*new).redir_in);
		return (ERROR);
	}
	
}

int	add_redir(t_data *data, char *token, t_token *new)
{
	t_redir	*redir_in;
	t_redir	*redir_out;

	add_redir_in(data, token, redir_in);
	add_redir_out(data, token, redir_out);
	add_in_struct(new, redir_in, redir_out);
	return (SUCCESS);
}

add_redir_in(t_data *data, char *token, t_redir *redir_in)
{
	char *tmp;
	char *result;

	while (*tmp)
	{
		while (*tmp && *tmp != '<')
			tmp++;
		tmp = token;
		while (*tmp && *tmp != ' ')
			tmp++;
		result = ft_substr(token, tmp - token);
		printf("result = %s\n", result);
	}
}