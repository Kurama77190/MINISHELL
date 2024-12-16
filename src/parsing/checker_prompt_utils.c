/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_prompt_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 03:21:51 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 06:00:12 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_redirection(char *str, int *i);
static bool	validate_pipe(char *str, int i);
static void	update_in_quote_checker(char c, char *in_quote);

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
	if (str[i] == '|')
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (false);
	}
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
			if (!validate_pipe(str, i))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	validate_pipe(char *str, int i)
{
	int	j;

	if (i == 0 || str[i + 1] == '\0')
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (false);
	}
	j = i + 1;
	while (str[j] == ' ')
		j++;
	if (str[j] == '|' || str[j] == '\0')
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (false);
	}
	if (i > 0 && (str[i - 1] == '<' || str[i - 1] == '>'))
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (false);
	}
	return (true);
}

bool	validate_redirection(char *str, int *i)
{
	int	j;

	// Gérer les doubles redirections (<< ou >>)
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i + 1] == '>'))
		(*i)++;

	// Vérifier si une redirection est suivie par une autre redirection
	j = *i + 1;
	while (str[j] && str[j] == ' ') // Ignorer les espaces après une redirection
		j++;
	if (str[j] == '<' || str[j] == '>') // Si une autre redirection suit
	{
		printf("bash: syntax error near unexpected token '%c'\n", str[j]);
		return (false);
	}

	// Vérifier si une redirection est suivie directement d'un pipe
	if (str[*i + 1] == '|')
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (false);
	}

	// Vérifier si une redirection est suivie uniquement par des espaces ou rien
	if (str[*i + 1] == '\0' || is_operator(str[*i + 1]))
	{
		j = *i + 1;
		while (str[j] && str[j] == ' ') // Ignorer les espaces
			j++;
		if (str[j] == '\0' || is_operator(str[j]))
		{
			printf("bash: syntax error near unexpected token '%c'\n", str[*i]);
			return (false);
		}
	}

	return (true);
}


static void	update_in_quote_checker(char c, char *in_quote)
{
	if ((c == '\'' || c == '\"') && *in_quote == 0)
		*in_quote = c;
	else if (c == *in_quote)
		*in_quote = 0;
}
