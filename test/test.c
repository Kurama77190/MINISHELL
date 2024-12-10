/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:24:39 by samy              #+#    #+#             */
/*   Updated: 2024/12/07 19:28:24 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *token = "caca pipi zizi < fichier";

int	add_redir_in(t_data *data, char *token, t_redir **redir_in)
{
	(void)data;
	char *tmp;
	char *result;
	char test[1024];
	t_type type;

	tmp = token;
	while (*tmp)
	{
		while (*tmp && *tmp != '<')
			tmp++;
		if (*tmp == '<' && *(tmp + 1) == '<')
			type |= HERE_DOC;
		else
			type |= REDIR_IN;
		tmp = token;
		while (*tmp && (*tmp != ' ' || *tmp + 1 != ' '))
			tmp++;
		result = ft_substr(token, *tmp, *tmp - *token);
		if (!result)
			return (ERROR);
		printf("result = %s\n", result);
		ft_strlcpy((*redir_in)->file_name, result, ft_strlen(result) + 1);
		printf("test = %s\n", test);
		(*redir_in)->type = type;
	}
	return (SUCCESS);
}

int main()
{
	t_redir *new;

	new = ft_calloc(1, sizeof(t_redir));
	add_redir_in(NULL, token, &new);
	printf("file name = %s\n", new->file_name);
	printf("type = %d\n", new->type);
	return (0);
}
// Compare this snippet from src/parsing/handle_redir.c: