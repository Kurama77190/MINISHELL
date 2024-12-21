/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/19 11:59:28 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, char *msg)
{
	ft_free_all(data, false);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

void	ft_error_child(t_data *data, char *msg)
{
	ft_free_all(data, true);
	ft_putstr_fd(msg, STDERR_FILENO);
	data->exit_status = 1;
}

void	ft_error_exit(t_data *data, char *msg)
{
	ft_error(data, msg);
	data->exit_status = 1;
	exit(1);
}

void	ft_error_quote(t_data *data)
{
	ft_putstr_fd("minishell> unexpected EOF while looking for matching ` or \"",
		STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
}
