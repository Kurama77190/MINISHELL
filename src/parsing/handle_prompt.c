/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:41:08 by samy              #+#    #+#             */
/*   Updated: 2024/12/07 00:41:28 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_prompt(t_data *data)
{
	data->prompt.read_line = readline("minishell-1.0$ ");
	if (!data->prompt.read_line)
	{
		ft_putstr_fd("exit\n", 2);
		// free_all;
		return (ERROR);
	}
	if (*(data->prompt.read_line))
		add_history(data->prompt.read_line);
	return (SUCCESS);
}
