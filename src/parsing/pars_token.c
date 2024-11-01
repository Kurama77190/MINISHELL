/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:00:51 by sben-tay          #+#    #+#             */
/*   Updated: 2024/11/01 06:02:33 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		identifier_token(t_data *data, char *token);

int	pars_token(t_data *data)
{
	int	i;

	data->token_manag.line = ft_strtrim(data->prompt.read_line, " ");
	data->token_manag.readed = ft_split(data->token_manag.line, '|');
	if (!data->token_manag.readed)
		return (ERROR);
	i = 0;
	while (data->token_manag.readed[i])
	{
		printf("token[%i] = %s\n", i, data->token_manag.readed[i]);
		if (identifier_token(data, data->token_manag.readed[i]) == ERROR)
			return (free_split(data->token_manag.readed), ERROR);
		i++;
	}
	free_split(data->token_manag.readed);
	return (SUCCESS);
}

int	identifier_token(t_data *data, char *token)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (ERROR);
	if (search_token(data, token, &new) == ERROR);
	{
		free(new); // et liberer son contenue aussi stp.
		return (ERROR);
	}
	add_back_token(data, new);
	return (SUCCESS);
}

int	search_token(t_data *data, char *token, t_token **new)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '<' || token[i] == '>')
		{
			set_redir(&new, token + i);
			i++;
		}
		while(token[i] && (token[i] != ' ' || token[i] != '<' || token[i] != '>'))
			i++;
		token = ft_substr(token, j, i);
		if (!token)
			return (ERROR);
		token_id(data, token, new);
		free(token);
		j = i;
		i++;
	}	
	return (SUCCESS);
}

int	add_back_token(t_data *data, t_token *new)
{
	t_token	*current;

	if (!data->token_manag.token)
	{
		data->token_manag.token = new;
		return (SUCCESS);
	}
	current = data->token_manag.token;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (SUCCESS);
}

int	token_id(t_data *data, char *token, t_token **new)
{
	if (is_args(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	if (is_builtin_1(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	if (is_builtin_2(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	if (is_builtin_3(data, token, new) == ERROR)
	{
		return (ERROR);
	}
	else
	{
		if (is_command(data, token, new) == ERROR)
		{
			return (ERROR);
		}
		
	}
	return (SUCCESS);
}

// ordre d execution absolu, peut importe l ordre et les commands donner a UNIX, celui ci l interpretre dans un ordre bien specifique,
// regarder les redir in and out et les set
// par la suite il regarde la commande et c arguments
// apres cela il pourra commencer le input, la commandes avec c arguments et son output !
// grace a ca nous pourrons peut importe ou se trouve la redirection sur la commande avoir exactement le meme comportement que minishell.
// ENJOY SBEN TAY! =D