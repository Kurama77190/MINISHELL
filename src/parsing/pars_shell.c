/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:43:37 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 20:03:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pars_here_doc(t_data *data);

int	pars_shell(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	uptdate_env(data);
	if (check_cmd(data) == ERROR)
	{
		return (ERROR);
	}
	if (pars_token(data) == ERROR)
	{
		ft_putstr_fd("Error in pars_token\n", 2);
		return (ERROR);
	}
	if (pars_expand(data) == ERROR)
	{
		return (ERROR);
	}
	if (pars_here_doc(data) == ERROR)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

static int	pars_here_doc(t_data *data)
{
	t_token	*current;

	current = data->token_manag.token;
	while (current)
	{
		if (ft_read_heredoc(current->redir_in.head, data) == ERROR)
			return (ERROR);
		current = current->next;
	}
	return (SUCCESS);
}
