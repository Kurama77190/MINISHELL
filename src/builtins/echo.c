/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/22 13:17:04 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verif_flag(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **argv)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (argv[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (verif_flag(argv[i]) == true)
	{
		n_flag = true;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == false)
		ft_putstr_fd("\n", 1);
	return (0);
}
