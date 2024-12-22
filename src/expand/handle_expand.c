/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:10:24 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/22 15:17:20 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_expand(t_data *data)
{
	t_redir	*current_in;
	t_redir	*current_out;
	t_token	*current_token;

	current_token = data->token_manag.token;
	while (current_token)
	{
		current_in = current_token->redir_in.head;
		current_out = current_token->redir_out.head;
		while (current_in)
		{
			if (ft_expand_redir(&current_in->file_name, data->e.envp) == ERROR)
				return (ERROR);
			current_in = current_in->next;
		}
		while (current_out)
		{
			if (ft_expand_redir(&current_out->file_name, data->e.envp) == ERROR)
				return (ERROR);
			current_out = current_out->next;
		}
		if (ft_expand_args(current_token->args, data->e.envp,
				data->exit_status) == ERROR)
		{
			data->exit_status = 127;
			return (ERROR);
		}
		current_token = current_token->next;
	}
	return (SUCCESS);
}
