/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:24:39 by samy              #+#    #+#             */
/*   Updated: 2024/12/13 02:27:25 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	found_args_cmd(char	*token, t_token	*new)
{
	
	return (SUCCESS);
}

int	setup_cmd(char *token, t_token *new)
{
	if (found_cmd_name(token, new) == ERROR)
		return (ERROR);
	// if (found_args_cmd() == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}

int	found_cmd_name(char *token, t_token *new)
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

int	main(void)
{
	t_token	*new;
	char	*token;

	while (1)
	{
		new = ft_calloc(1, sizeof(t_token));
		token = readline("MINISHELL TEST ");
		if (!token)
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		found_cmd_name(token, new);
		printf("[command] :%s [adress]%p\n", new->command, new->command);
		free(new->command);
		memset(new, 0, sizeof(t_token));
		free(token);
		free(new);
	}
	return (0);
}
// Compare this snippet from src/parsing/handle_redir.c: