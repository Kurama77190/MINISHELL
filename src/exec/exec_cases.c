/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:56:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/21 12:15:39 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

// void	multi_pipe(t_ast_node *node, t_data *data, int i)
// {
// 	read_infile(node, data);
//     read_outfile(node, data);
// 	if (i == 0)
// 	{
// 		node->pid = fork();
// 		if (node->pid == -1)
// 			ft_error(data, "Error forking");
// 		if (node->pid == 0)
// 		{
// 			dup2(data->fd[1], STDOUT_FILENO);
// 			if (is_builtin(node->argv[0]) == true)
// 			{
// 				ft_detect_builtin(node->argv, data);
// 				ft_free_all(data);
// 			}
// 			else
// 				exec(data, node->argv);
// 			exit(1);
// 		}
// 	}

// 	if (i > 0 && i < data->nb_levels)
// 	{
// 		node->pid = fork();
// 		if (node->pid == -1)
// 			ft_error(data, "Error forking");
// 		if (node->pid == 0)
// 		{
// 			dup2(data->fd[0], STDIN_FILENO);
// 			dup2(data->fd[1], STDOUT_FILENO);
// 			if (is_builtin(node->argv[0]) == true)
// 			{
// 				ft_detect_builtin(node->argv, data);
// 				ft_free_all(data);
// 			}
// 			else
// 				exec(data, node->argv);
// 			exit(1);
// 		}
// 	}

// 	if (i == data->nb_levels)
// 	{
// 		close(data->fd[1]);
// 		node->pid = fork();
// 		if (node->pid == -1)
// 			ft_error(data, "Error forking");
// 		if (node->pid == 0)
// 		{
// 			dup2(data->fd[0], STDIN_FILENO);
// 			if (is_builtin(node->argv[0]) == true)
// 			{
// 				ft_detect_builtin(node->argv, data);
// 				ft_free_all(data);
// 			}
// 			else
// 				exec(data, node->argv);
// 			exit(1);
// 		}
// 		close(data->fd[0]);
// 		waitpid(node->pid, NULL, 0);
// 	}

// 	// if (dup2(data->stdin_backup, STDIN_FILENO) == -1 || dup2(data->stdout_backup,
//     //         STDOUT_FILENO) == -1)
//     //     ft_error(data, "Error restoring stdin/stdout");
// }

int	ft_erase_all_temp_here_doc(t_redir *node)
{
	t_redir	*current;

	current = node;
	while (current)
	{
		if (current->key == D_HEREDOC && current->file_here_doc != NULL)
		{
			unlink(current->file_here_doc);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	ft_multi_pipe_child(t_token *node, t_data *data)
{
	if (node->args)
	{
		if (is_builtin(node->args[0]))
		{
			ft_detect_builtin(node->args, data);
			ft_free_all(data, true);
			exit(data->exit_status);
		}
		else
		{
			if (ft_exec_cmd(data, node) == ERROR)
			{
				ft_free_all(data, true);
				exit(1);
			}
		}
	}
	return (SUCCESS);
}

int	ft_multi_pipe(t_token *node, t_data *data)
{
	pid_t	pid;

	ft_read_heredoc(node->redir_in.head, data);
	pipe(node->fd_pipe);
	ft_exec_redirs(node, data);
	pid = fork();
	if (pid == -1)
		ft_error(data, "Error forking");
	node->pid = pid;
	if (pid == 0)
	{
		ft_multi_pipe_child(node, data);
	}
	return (SUCCESS);
}

int	ft_no_pipe(t_token *node, t_data *data)
{
	ft_exec_redirs(node, data);
	if (node && node->args && is_builtin(node->args[0]))
	{
		ft_exec_redirs(node, data);
		ft_detect_builtin(node->args, data);
	}
	else
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking\n");
		if (node->pid == 0)
		{
			if (ft_exec_cmd(data, node) == ERROR)
			{
				ft_free_all(data, true);
				exit(1);
			}
		}
	}
	return (SUCCESS);
}
