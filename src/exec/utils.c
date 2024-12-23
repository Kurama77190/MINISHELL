/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:09 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/23 22:29:06 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_count_levels(t_token *node, int level, t_data *data)
// {
// 	if (!node)
// 		return ;
// 	data->nb_levels = level;
// 	if (node->next)
// 		ft_count_levels(node->next, level + 1, data);
// }

// void	wait_commands(t_data *data)
// {
// 	signal(SIGINT, SIG_IGN);
// 	while (errno != ECHILD)
// 	{
// 		if (wait(&data->wstatus) == data->last_pid)
// 		{
// 			if (WIFEXITED(data->wstatus))
// 				data->exit_status = WEXITSTATUS(data->wstatus);
// 			else
// 			{
// 				data->exit_status = 128 + WTERMSIG(data->wstatus);
// 				if (data->exit_status == 131)
// 					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
// 				else if (data->exit_status == 139)
// 					ft_putstr_fd("Segmentation fault (core dumped)\n",
// 						STDERR_FILENO);
// 			}
// 			if (data->exit_status == 130)
// 				ft_putstr_fd("\n", STDERR_FILENO);
// 		}
// 	}
// 	if (g_exit_status == 130)
// 		data->exit_status = 130;
// }

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

bool	is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd") \
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env") \
		|| !ft_strcmp(command, "exit"))
		return (true);
	return (false);
}

// void	close_hd(t_redir *redir, t_data *data)
// {
// 	(void)redir;
// 	close(STDIN_FILENO);
// 	if (data && data->fd[0] != -1)
// 		close(data->fd[0]);
// }

void	ft_close_fd(t_data *data, t_token *token, char *msg)
{
	if (token->fd_in != -1)
		close(token->fd_in);
	if (token->fd_out != -1)
		close(token->fd_out);
	data->exit_status = 1;
	perror(msg);
	ft_free_all(data, true);
}
