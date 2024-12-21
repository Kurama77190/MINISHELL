/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:41:08 by samy              #+#    #+#             */
/*   Updated: 2024/12/21 11:49:36 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_prompt(t_data *data)
{
	data->prompt.read_line = readline("minishell-1.0$ ");
	if (!data->prompt.read_line)
	{
		ft_free_all(data, true);
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (*(data->prompt.read_line))
		add_history(data->prompt.read_line);
}
