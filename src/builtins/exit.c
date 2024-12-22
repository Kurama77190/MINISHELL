/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/22 09:32:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_value(int value)
{
	if (value > 255 || value < 0)
		value = (value % 256 + 256) % 256;
	return (value);
}

void	ft_exit(char **argv, t_data *data)
{
	int		value;

	value = 0;
	if (argv[1] && !ft_is_number(argv[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		ft_free_all(data, true);
		exit(2);
	}
		
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(1);
		return ;
	}
	if (argv[1])
	{
		if (ft_is_number(argv[1]))
		{
			value = ft_atoi(argv[1]);
			value = ft_value(value);
			ft_free_all(data, true);
			exit(value);
		}
		else
			ft_error(data, "exit: numeric argument required\n");
	}
	else
	{
		ft_free_all(data, true);
		exit(0);
	}
}
