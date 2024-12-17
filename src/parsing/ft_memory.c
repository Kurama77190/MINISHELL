/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:51:32 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/17 22:55:12 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_memory(t_data *data)
{
	memset(&data->prompt, 0, sizeof(t_prompt));
	memset(&data->token_manag, 0, sizeof(t_token_manag));
	// rajouter les structures de ralph.
}

void	ft_free_all_child(t_data *data)
{
	free_envp(data);
	ft_free((void**)&data->prompt.read_line);
	free_token(data);
}

void	ft_free_all(t_data *data, bool	free_env)
{
	if (free_env)
		free_envp(data);
	ft_free((void**)&data->prompt.read_line);
	free_token(data);
	// if (data->free_value == 0)
	// {
	// 	close(data->fd[0]);
	// 	close(data->fd[1]);
	// }
	// rajouter les free de ralph.
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
		ft_free((void**)&current->line);
		next = current->next;
		ft_free((void **)&current);
		current = next;
	}
	data->e.envp = NULL;
	free_split(data->e.env);
}

void	free_token(t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	current = data->token_manag.token;
	while(current)
	{
		free_redir(current);
		free_split(current->args);
		ft_free((void**)&current->command);
		tmp = current->next;
		ft_free((void**)&current);
		current = tmp;
	}
	ft_free((void**)&current);
}

void	free_redir(t_token *current)
{
	t_redir	*current_in;
	t_redir	*current_out;
	t_redir	*tmp;

	current_in = current->redir_in.head;
	current_out = current->redir_out.head;
	while(current_in)
	{
		ft_free((void**)&current_in->file_name);
		ft_free((void**)&current_in->type);
		ft_free((void**)&current_in->file_here_doc);
		tmp = current_in->next;
		ft_free((void**)&current_in);
		current_in = tmp;
	}
	// ft_free((void**)&current_out);
	while(current_out)
	{
		ft_free((void**)&current_out->file_name);
		ft_free((void**)&current_out->type);
		ft_free((void**)&current_out->file_here_doc);
		tmp = current_out->next;
		ft_free((void**)&current_out);
		current_out = tmp;
	}
	// ft_free((void**)&current_out);
}

//valgrind --suppressions=ignore.txt ./minishell
