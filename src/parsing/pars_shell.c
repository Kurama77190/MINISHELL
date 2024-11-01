/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:43:37 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/29 19:31:41 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_shell(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (!data->envp_manag.sync)
		uptdate_env(data);
	if (pars_token(data) == ERROR)
	{
		ft_putstr_fd("Error in pars_token\n", 2);
		// free_all;
		// exit(2)
		return (ERROR);
	}
	// pars_sig(); // signaux
	return (SUCCESS);
}
