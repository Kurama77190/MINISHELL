/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 07:05:42 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

void	put_tokenizer_data(t_data *data);

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
