/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 03:21:51 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 21:37:19 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_pipe_syntax(char *str, int i);
bool	is_pipe_start_or_end(char *str, int i);
bool	check_double_redirection(char *str, int *i);
bool	check_following_chars(char *str, int *i, int j);
void	update_in_quote_checker(char c, char *in_quote);
bool	validate_redirection(char *str, int *i);

bool	check_redirection(char *str)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		update_in_quote_checker(str[i], &in_quote);
		if (!in_quote && str[i] == ' ')
		{
			i++;
			continue ;
		}
		if (!in_quote && (str[i] == '<' || str[i] == '>'))
		{
			if (!validate_redirection(str, &i))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	check_pipe(char *str)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (is_pipe_start_or_end(str, i))
		return (false);
	while (str[i])
	{
		update_in_quote_checker(str[i], &in_quote);
		if (!in_quote && str[i] == ' ')
		{
			i++;
			continue ;
		}
		if (!in_quote && str[i] == '|')
		{
			if (!validate_pipe_syntax(str, i))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	validate_redirection(char *str, int *i)
{
	int j;

	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i + 1] == '>'))
		(*i)++;
	j = *i + 1;
	while (str[j] && str[j] == ' ')
		j++;
	if (str[j] == '\0' || str[j] == '<' || str[j] == '>')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(str[*i], 2);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	return (true);
}

bool	check_unclosed_quotes(const char *str)
{
	char	in_quote;
	int		i;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && in_quote == 0)
			in_quote = str[i];
		else if (str[i] == in_quote)
			in_quote = 0;
		i++;
	}
	if (in_quote != 0)
	{
		ft_putstr_fd("bash: syntax error: unclosed quote\n", 2);
		return (false);
	}
	return (true);
}
