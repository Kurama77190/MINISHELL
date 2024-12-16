/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 03:30:00 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 06:29:49 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_empty_prompt(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	update_in_quote_checker(char c, char *in_quote)
{
	if ((c == '\'' || c == '\"') && *in_quote == 0)
		*in_quote = c;
	else if (c == *in_quote)
		*in_quote = 0;
}
