/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 06:24:52 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 06:31:21 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	validate_pipe_syntax(char *str, int i)
{
	int	j;

	j = i + 1;
	while (str[j] == ' ')
		j++;
	if (str[j] == '|' || str[j] == '\0')
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (false);
	}
	if (i > 0 && (str[i - 1] == '<' || str[i - 1] == '>'))
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (false);
	}
	return (true);
}

bool	is_pipe_start_or_end(char *str, int i)
{
	if (str[i] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (true);
	}
	return (false);
}

bool	check_double_redirection(char *str, int *i)
{
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i + 1] == '>'))
		(*i)++;
	return (false);
}

bool	check_following_chars(char *str, int *i, int j)
{
	if (str[j] == '<' || str[j] == '>')
	{
		ft_putstr_fd("bash: syntax error near unexpected token ", 2);
		ft_putchar_fd(str[j], 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	if (str[*i + 1] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (false);
	}
	if (str[*i + 1] == '\0' || is_operator(str[*i + 1]))
	{
		while (str[j] && str[j] == ' ')
			j++;
		if (str[j] == '\0' || is_operator(str[j]))
		{
			ft_putstr_fd("bash: syntax error near unexpected token ", 2);
			ft_putchar_fd(str[*i], 2);
			ft_putstr_fd("\n", 2);
			return (false);
		}
	}
	return (true);
}
