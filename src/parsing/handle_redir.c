/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:42:18 by samy              #+#    #+#             */
/*   Updated: 2024/12/17 03:20:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_redir_with_spaces(char *token, int *i, char redir);
int	handle_redirection(char *token, int *i, t_redir_manag *redir);
int	update_in_quote(char c, int in_quote);

int	setup_redir(char *token, t_token *new)
{
	int				in_quote;
	int				i;

	in_quote = 0;
	i = 0;
	while (token[i])
	{
		in_quote = update_in_quote(token[i], in_quote);
		if (!in_quote && (token[i] == '<' || token[i] == '>'))
		{
			if (handle_redirection(token, &i, &new->redir_in) == ERROR)
				return (ERROR);
		}
			i++;
	}
	return (SUCCESS);
}

void	replace_redir_with_spaces(char *token, int *i, char redir)
{
	while (token[*i] == redir)
	{
		token[*i] = ' ';
		(*i)++;
	}
	while (token[*i] && !ft_isspace(token[*i])
		&& token[*i] != '<' && token[*i] != '>')
	{
		token[*i] = ' ';
		(*i)++;
	}
}

int	handle_redirection(char *token, int *i, t_redir_manag *redir)
{
	if (token[*i] == '<')
	{
		if (add_redir_in(token + *i, redir) == ERROR)
			return (ERROR);
	}
	else if (token[*i] == '>')
	{
		if (add_redir_out(token + *i, redir) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	update_in_quote(char c, int in_quote)
{
	if (c == '\'' && in_quote != 2)
	{
		if (in_quote == 0)
			return (1);
		else if (in_quote == 1)
			return (0);
	}
	else if (c == '\"' && in_quote != 1)
	{
		if (in_quote == 0)
			return (2);
		else if (in_quote == 2)
			return (0);
	}
	return (in_quote);
}
