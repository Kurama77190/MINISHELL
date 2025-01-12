/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 08:50:33 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	pars_env(&data, env);
	while (1)
	{
		signals();
		handle_prompt(&data);
		if (pars_shell(&data, argc, argv) != ERROR)
		{
			ft_execution(&data);
			pid_controller(&data);
		}
		ft_free_all(&data, false);
		ft_memory(&data);
	}
	return (0);
}
