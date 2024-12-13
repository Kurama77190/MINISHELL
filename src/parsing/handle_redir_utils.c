/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:04:51 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/13 05:47:39 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_word(char *str, size_t i, unsigned int start)
{
	if (!str)
		return ;
	while (*str && i > start)
	{
		*str = ' ';
		str++;
		i--;
	}
}
void	found_index(char *tmp, int *i)
{
	int	in_quote;

	in_quote = 0;
	while (tmp[*i])
	{
		if (tmp[*i] == '"' || tmp[*i] == '\'')
		{
			if (in_quote == 0)
				in_quote = tmp[*i];
			else if (in_quote == tmp[*i])
				in_quote = 0;
		}
		else if (!in_quote && (ft_isspace(tmp[*i]) || ft_is_operator(tmp[*i])))
			break;
		(*i)++;
	}
}

bool	is_operator_in_quotes(char *token, char operator)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while(token[i] && token[i] != operator)
	{
		if (token[i] == '\"')
			d_quote = !d_quote;
		if (token[i] == '\'')
			s_quote = !s_quote;
		i++;
	}
	if (!token[i])
		return (true);
	if (s_quote || d_quote)
	{
		return (true);
	}
	return (false);
}
