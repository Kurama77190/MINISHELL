/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:15:45 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/15 19:54:38 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	handle_lex(t_data *data)
{
	// check_valid_cmd
	if (check_quote == ERROR)
	{
		return (ERROR);
	}
}


int	check_valid_cmd(t_data *param)
{
	
}

int	check_quote(t_data *param)
{
	t_token			*current_token;
	t_redir_manag	*current_redir_in;
	t_redir_manag	*current_redir_out;

	current_token = param->token_manag.token;
	current_redir_in = &current_token->redir_in;
	current_redir_out = &current_token->redir_out;

	// check_redir_in
	// check_redir_out
	// check_cmd
	// check_args
	return (SUCCESS);
}

int	check_redir_in(t_redir	*current_in)
{
	
}


int	closed_quote_(char *str)
{
	int	d_closed;
	int	s_closed;
	int	i;

	d_closed = 0;
	s_closed = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == "\'")
			s_closed += !s_closed;
		if (str[i] == "\"")
			d_closed += !d_closed;
		i++;
	}
	if (!d_closed || !s_closed)
		return (0);
	return (1);
}