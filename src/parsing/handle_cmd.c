/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 02:26:22 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/13 02:32:51 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	found_cmd_name(char *token, t_token *new);

int	setup_cmd(char *token, t_token *new)
{
	if (found_cmd_name(token, new) == ERROR)
		return (ERROR);
	// if (found_args_cmd() == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}

static int	found_cmd_name(char *token, t_token *new)
{
	int	j;
	int	cote;

	cote = 0;
	while (*token && ft_isspace(*token) && (*token != '\"' \
			|| *token != '\''))
		token++;
	if (!(*token))
		return (SUCCESS);
	j = 0;
	while (token[j] && ((cote != 2 && !ft_isspace(token[j])) || cote == 1))
	{
		if (token[j] == '\"' || token[j] == '\'')
		{
			if (cote == 0)
				cote = 1;
			else if (cote == 1)
				cote = 0;
		}
		j++;
	}
	new->command = ft_substr(token, 0, j);
	if (!new->command)
		return (ERROR);
	return (SUCCESS);
}
