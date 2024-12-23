/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_controler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:19:48 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 20:01:58 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pid_controller(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_manag.token;
	if (!tmp->next && !tmp->prev && tmp->builtin)
		return (ERROR);
	while (tmp)
	{
		waitpid(tmp->pid, &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		else if (WIFSIGNALED(data->exit_status))
			data->exit_status = WTERMSIG(data->exit_status) + 128;
		ft_erase_all_temp_here_doc(tmp->redir_in.head);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
