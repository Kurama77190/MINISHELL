/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:10:24 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 04:21:09 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_expand_in(t_data *data, t_redir *current_in);

char	*ft_remove_quotes(char *str)
{
	size_t	len;
	char	quote;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (str);
	quote = str[0];
	if ((quote == '\'' || quote == '"') && str[len - 1] == quote)
	{
		new_str = (char *)malloc(sizeof(char) * (len - 1));
		if (!new_str)
			return (NULL);
		ft_strlcpy(new_str, str + 1, len - 1);
		free(str);
		return (new_str);
	}
	return (str);
}

int	pars_expand(t_data *data)
{
	t_redir	*current_in;
	t_redir	*current_out;
	t_token	*current_token;

	current_token = data->token_manag.token;
	while (current_token)
	{
		current_in = current_token->redir_in.head;
		current_out = current_token->redir_out.head;
		set_expand_in(data, current_in);
		while (current_out)
		{
			if (ft_expand_args(&current_out->file_name, data->e.envp,
					data->exit_status) == ERROR)
				return (ERROR);
			current_out = current_out->next;
		}
		if (ft_expand_args(current_token->args, data->e.envp,
				data->exit_status) == ERROR)
			return (data->exit_status = 127, ERROR);
		current_token = current_token->next;
	}
	return (SUCCESS);
}

static int	set_expand_in(t_data *data, t_redir *current_in)
{
	while (current_in)
	{
		if (current_in->key == D_HEREDOC)
		{
			current_in->file_name = ft_remove_quotes(current_in->file_name);
		}
		else if (ft_expand_args(&current_in->file_name, data->e.envp,
				data->exit_status) == ERROR)
			return (ERROR);
		current_in = current_in->next;
	}
	return (SUCCESS);
}
