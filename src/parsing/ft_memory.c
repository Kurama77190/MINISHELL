/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:51:32 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 21:46:01 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_memory(t_data *data)
{
	memset(&data->prompt, 0, sizeof(t_prompt));
	memset(&data->token_manag, 0, sizeof(t_token_manag));
	data->path_env = NULL;
}

void	ft_free_all_child(t_data *data)
{
	free_envp(data);
	ft_free((void **)&data->prompt.read_line);
	free_split(data->path_env);
	free_token(data);
}

void	ft_free_all(t_data *data, bool free_env)
{
	if (free_env)
	{
		clear_history();
		free_envp(data);
	}
	ft_free((void **)&data->prompt.read_line);
	free_token(data);
	free_split(data->path_env);
}

void	free_envp(t_data *data)
{
	t_envp	*current;
	t_envp	*next;

	current = data->e.envp;
	if (!current)
		return ;
	while (current)
	{
		ft_free((void **)&current->name);
		ft_free((void **)&current->value);
		ft_free((void **)&current->line);
		next = current->next;
		ft_free((void **)&current);
		current = next;
	}
	data->e.envp = NULL;
	free_split(data->e.env);
}

void	ft_free_children(t_data *data, int erro)
{
	ft_free_all(data, true);
	exit(erro);
}
