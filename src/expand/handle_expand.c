/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 06:39:08 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 07:27:29 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_expand(t_token *param)
{
	if (expand_redir(param) == ERROR)
		return (ERROR);
	if (expand_cmd(param) == ERROR)
		return (ERROR);
	if (expand_args(param) == ERROR)
		return (ERROR);
}
