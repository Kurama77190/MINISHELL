/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/17 02:35:10 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		data.param.read_line = readline("minishell-1.0$ ");
		if (!data.param.read_line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*(data.param.read_line))
		{
			add_history(data.param.read_line);
		}
		// pars_cmd(data);

		//exec_command. a noter que a chaque fois que tu executes une
		// commande tu dois reset la structure entiere.
		free(data.param.read_line);
	}
	return (0);
}