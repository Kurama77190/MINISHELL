/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/09 14:02:03 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	verif_flag(char *str)
{
	int	i;

	i = 1;
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

void	ft_echo(char **argv, t_data *data)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (argv[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (verif_flag(argv[i]) == true)
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
	data->exit_status = 0;
}
