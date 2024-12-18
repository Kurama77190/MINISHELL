/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_controler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:19:48 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/19 00:19:07 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_pid(t_token *current, int *exit_status)
{
	int		status;
	pid_t	pid;

	pid = waitpid(current->pid, &status, WNOHANG);
	if (pid == 0)
		return (0); // Processus en cours d'exécution
	else if (pid > 0)
	{
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd("\nQuit (core dumped)", 1);
			*exit_status = 128 + WTERMSIG(status);
		}
		current->pid = -1;
	}
	return (1);
}

static int	process_tokens(t_data *data, int *all_terminated)
{
	t_token	*current;
	int		terminated;

	current = data->token_manag.token;
	while (current)
	{
		if (current->pid > 0)
		{
			terminated = handle_pid(current, &data->exit_status);
			if (!terminated)
				*all_terminated = 0;
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	pid_controller(t_data *data)
{
	int	all_terminated;

	while (1)
	{
		all_terminated = 1;
		if (process_tokens(data, &all_terminated) == ERROR)
			return (ERROR);
		if (all_terminated)
			break ;
		usleep(1000);
	}
	ft_erase_all_temp_here_doc(data->token_manag.token->redir_in.head);
	return (SUCCESS);
}
