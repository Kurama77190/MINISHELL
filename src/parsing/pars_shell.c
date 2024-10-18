/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:43:37 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/19 00:49:28 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_shell(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (pars_env(data, envp) == ERROR)
	{
		ft_putstr_fd("Error in pars_env\n", 2);
		return (ERROR);
	}
	if (!data->envp.sync)
		uptdate_env(data);
	// pars_token();
	// pars_sig(); // signaux
	return (SUCCESS);
}
