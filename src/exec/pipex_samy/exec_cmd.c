/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:13:44 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 21:37:19 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_access_absolut_path_cmd(t_data *data, char **cmd_path);
int		ft_search_path_cmd(t_data *data, t_token *token);
int		ft_exec_absolut_path_cmd(t_data *data, t_token *token);

/* ************************************ */
/*  🌟 CHECK_ABSOLUT_PATH_AND_EXEC 🌟  */
/* ************************************ */

int	ft_exec_cmd(t_data *data, t_token *token)
{
	if (!token->command)
		ft_free_children(data, 0);
	if (is_solo_duo_point(&token->command[0]))
		ft_free_children(data, 2);
	if (data->e.env[0] == NULL)
	{
		if (ft_exec_without_envp_set(data, token) == ERROR)
			return (ERROR);
	}
	if (ft_strchr(token->args[0], '/') != NULL)
	{
		if (ft_exec_absolut_path_cmd(data, token) == ERROR)
			return (ERROR);
	}
	else if (ft_strchr(token->args[0], '/') == NULL)
	{
		if (ft_search_path_cmd(data, token) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/* ********************************* */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH 🌟  */
/* ********************************* */

int	ft_exec_absolut_path_cmd(t_data *data, t_token *token)
{
	if (ft_check_access_absolut_path_cmd(data, token->args) != 1)
	{
		if (execve(token->args[0], token->args, data->e.env) == ERROR)
		{
			perror("bash: execve: ");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/* *********************************** */
/*  🌟 SEARCH_PATH_CMD_AND_EXECVE 🌟  */
/* *********************************** */

int	ft_search_path_cmd(t_data *data, t_token *token)
{
	token->command = get_cmd(data, token);
	if (token->command != NULL)
	{
		if (execve(token->command, token->args, data->e.env) == ERROR)
		{
			ft_free_all(data, true);
			ft_error_msg("execve");
			return (ERROR);
		}
	}
	else
	{
		ft_free_all(data, true);
		ft_error_msg("execve");
		return (ERROR);
	}
	return (SUCCESS);
}
/* **************************************** */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH_HELPER 🌟  */
/* **************************************** */

int	ft_check_access_absolut_path_cmd(t_data *data, char **cmd_path)
{
	if (access(cmd_path[0], F_OK) == -1)
	{
		ft_error_file_directory(cmd_path[0]);
		ft_free_all(data, true);
		exit(127);
		return (ERROR);
	}
	if (access(cmd_path[0], X_OK) == -1)
	{
		ft_error_permission(cmd_path[0]);
		ft_free_all(data, true);
		exit(126);
		return (ERROR);
	}
	else
		return (SUCCESS);
}
