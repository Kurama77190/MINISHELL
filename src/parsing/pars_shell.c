/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:43:37 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 07:07:34 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// pars_sig(); // signaux
	return (SUCCESS);
}
