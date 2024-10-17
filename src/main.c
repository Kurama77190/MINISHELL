/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/17 05:53:03 by sben-tay         ###   ########.fr       */
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
		data.prompt.read_line = readline("minishell-1.0$ ");
		if (!data.prompt.read_line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*(data.prompt.read_line))
		{
			add_history(data.prompt.read_line);
		}
		// pars_cmd(data);

		//exec_command(data);
		
		//free_token_list(data);

		free(data.prompt.read_line);
		ft_memset(&data, 0, sizeof(t_data));
	}
	return (0);
}