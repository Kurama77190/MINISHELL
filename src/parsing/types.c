/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:33:25 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/05 16:34:05 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_id(t_data *data, char *token, t_token **new)
{
	if (is_args(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	if (is_builtin_1(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	if (is_builtin_2(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	if (is_builtin_3(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	else
	{
		if (is_command(data, token, new) == ERROR)
		{
			return (ERROR);
		}
		
	}
	return (SUCCESS);
}

int	is_args();

int	is_builtin_1();