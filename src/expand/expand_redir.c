/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:06:12 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 07:45:26 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	expand_redir(t_token *data)
{
	t_redir_manag	*current_in;
	t_redir_manag	*current_out;

	current_in = &data->redir_in;
	current_out = &data->redir_out;
	if (check_unclosed_quote_in(current_in) == ERROR)
		return (ERROR);
	if (check_unclosed_quote_out(current_out) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	check_unclosed_quote_in(t_redir_manag	*tmp)
{
	while(tmp->current)
	if (is_closed(tmp->current->file_name) == ERROR)
	{
		ft_putstr_fd("bash: expand: unclosed quote redir_in\n", 2);
		return (ERROR);
	}
	if (is_closed(tmp->current->type) == ERROR)
	{
		ft_putstr_fd("bash: expand: unclosed quote redir_in\n", 2);
		return (ERROR);
	}
}

int	check_unclosed_quote_out(t_redir_manag *tmp)
{
	t_redir	*current;

	current = tmp->head;
	while (current)
	{
		if (!is_closed(current->file_name))
		{
			ft_putstr_fd("bash: expand: unclosed quote in redir_out\n", 2);
			return (ERROR);
		}
		if (erased_quote(current->file_name) == ERROR)
			return (ERROR);
		if (!is_closed(current->type))
		{
			ft_putstr_fd("bash: expand: unclosed quote in redir_out\n", 2);
			return (ERROR);
		}
		erased_quote(current->key);
		if (define_key_type(current->key) == ERROR)
			return (ERROR);
		current = current->next;
	}
	return (SUCCESS);
}

int	update_redir_field(char **field)
{
	char	*new_field;

	if (!field || !*field)
		return (ERROR);
	new_field = erased_quote(*field);
	if (!new_field)
		return (ERROR);
	free(*field);
	*field = new_field;
}


char	*erased_quote(const char *str)
{
	int		i;
	int		j;
	char	in_quote;
	char	*result;

	if (!str)
		return (NULL);
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && in_quote == 0)
			in_quote = str[i];
		else if (str[i] == in_quote)
			in_quote = 0;
		else
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	return (result);
}	
