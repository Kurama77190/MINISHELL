/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:13:44 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/19 18:14:19 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_access_absolut_path_cmd(char **cmd_path);
int		ft_secure_cmd_empty(t_data *data, int i);
int		ft_exec_absolut_path_cmd(t_data *data, int i);
int		ft_search_path_cmd(t_data *data, int i);

/* ************************************ */
/*  🌟 CHECK_ABSOLUT_PATH_AND_EXEC 🌟  */
/* ************************************ */

int	ft_exec_cmd(t_data *data, int i)
{
	if (data->envp[0] == NULL)
	{
		if (ft_exec_without_envp_set(data, i) == ERROR)
			return (ERROR);
	}
	if (ft_strchr(data->argv[i], '/') != NULL)
	{
		if (ft_exec_absolut_path_cmd(data, i) == ERROR)
			return (ERROR);
	}
	else if (ft_strchr(data->argv[i], '/') == NULL)
	{
		if (ft_search_path_cmd(data, i) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/* ********************************* */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH 🌟  */
/* ********************************* */

int	ft_exec_absolut_path_cmd(t_data *data, int i)
{
	data->cmd = ft_split(data->argv[i], ' ');
	if (data->cmd[0] == NULL)
		return (ft_error_msg("Error_split"), ERROR);
	if (ft_check_access_absolut_path_cmd(data->cmd) == SUCCESS)
	{
		if (execve(data->cmd[0], data->cmd, data->envp) == ERROR)
		{
			ft_error_msg("execve");
			free_split(data->cmd);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/* *********************************** */
/*  🌟 SEARCH_PATH_CMD_AND_EXECVE 🌟  */
/* *********************************** */

int	ft_search_path_cmd(t_data *data, int i)
{
	if (ft_secure_cmd_empty(data, i) == ERROR)
		exit(127);
	data->cmd = ft_split(data->argv[i], ' ');
	if (!data->cmd)
		return (ft_error_msg("Error split"), ERROR);
	data->path = get_cmd(data, i);
	if (!data->path)
	{
		free_split(data->cmd);
		ft_lstclear(&data->data_pid, free);
		exit(127);
	}
	if (execve(data->path, data->cmd, data->envp) == ERROR)
	{
		free(data->path);
		free_split(data->cmd);
		ft_error_msg("execve");
		return (ERROR);
	}
	return (SUCCESS);
}

/* ****************************************** */
/*  🌟 SEARCH_PATH_CMD_AND_EXECVE_HELPER 🌟  */
/* ****************************************** */

int	ft_secure_cmd_empty(t_pipex *data, int i)
{
	if (ft_only_space(data->argv[i]) || data->argv[i][0] == '\0')
	{
		ft_error_cmd(data->argv[i]);
		ft_lstclear(&data->data_pid, free);
		return (ERROR);
	}
	else
		return (SUCCESS);
}

/* **************************************** */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH_HELPER 🌟  */
/* **************************************** */

int	ft_check_access_absolut_path_cmd(char **cmd_path)
{
	if (access(cmd_path[0], F_OK) == ERROR)
	{
		ft_error_file_directory(cmd_path[0]);
		free_split(cmd_path);
		return(ERROR);
	}
	if (access(cmd_path[0], X_OK) == ERROR)
	{
		ft_error_permission(cmd_path[0]);
		free_split(cmd_path);
		return(ERROR);
	}
	else
		return (SUCCESS);
}
