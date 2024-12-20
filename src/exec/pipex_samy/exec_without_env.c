/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_without_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:46:31 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/19 18:15:39 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_in_bin(t_data *data, int i);
int	ft_secure_cmd_empty_without_envp(t_data *data, int i);
int	ft_exec_absolut_path_cmd_without_envp(t_data *data, int i);
int	ft_check_access_without_envp(char **cmd_path, int i);
int	ft_check_access_bin_without_envp(char *cmd_path, int i, t_data *data);

/* ************************** */
/*  🌟 EXEC_WITHOUT_ENVP 🌟  */
/* ************************** */

int	ft_exec_without_envp_set(t_data *data, int i)
{
	if (ft_strchr(data->argv[i], '/') != NULL)
	{
		if (ft_exec_absolut_path_cmd_without_envp(data, i) == ERROR)
			return (ERROR);
	}
	if (ft_strchr(data->argv[i], '/') == NULL)
	{
		if (ft_exec_in_bin(data, i) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/* ******************************* */
/*  🌟 EXEC_COMMANDS_BIN_ONLY 🌟  */
/* ******************************* */

int	ft_exec_in_bin(t_data *data, int i)
{
	if (ft_secure_cmd_empty(data, i) == ERROR)
		exit(127);
	data->cmd = ft_split(data->argv[i], ' ');
	if (!data->cmd)
		return (ft_error_msg("Error split"));
	data->path = ft_strjoin("/bin/", data->cmd[0]);
	if (!data->path)
	{
		free_split(data->cmd);
		return (ft_error_msg("Error split"));
	}
	if (ft_check_access_bin_without_envp(data->path, i, data) == SUCCESS)
	{
		if (execve(data->path, data->cmd, data->envp) == ERROR)
		{
			free(data->path);
			free_split(data->cmd);
			ft_error_msg("execve");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/* ****************************************** */
/*  🌟 SEARCH_PATH_CMD_AND_EXECVE_HELPER 🌟  */
/* ****************************************** */

int	ft_secure_cmd_empty_without_envp(t_data *data, int i)
{
	if (ft_only_space(data->argv[i]) || data->argv[i][0] == '\0')
	{
		if (data->envp[0] == NULL && (i == 2 || i == 1 || i == 0))
			ft_error_cmd_envp(data->argv[i]);
		else
			ft_error_cmd(data->argv[i]);
		ft_lstclear(&data->data_pid, free);
		return (ERROR);
	}
	else
		return (SUCCESS);
}

/* ********************************************* */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH_WHITOUT_ENV 🌟  */
/* ********************************************* */

int	ft_exec_absolut_path_cmd_without_envp(t_data *data, int i)
{
	data->cmd = ft_split(data->argv[i], ' ');
	if (data->cmd == NULL)
		return (ft_error_msg("Error_split"), ERROR);
	if (ft_check_access_without_envp(data->cmd, i) == SUCCESS)
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

/* **************************************************** */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH_WHITOUT_ENV_HELPER 🌟  */
/* **************************************************** */

int	ft_check_access_without_envp(char **cmd_path, int i)
{
	if (access(cmd_path[0], F_OK) == ERROR)
	{
		if (i == 2 || i == 1)
			ft_error_cmd_envp(cmd_path[0]);
		else if (ft_strchr(cmd_path[0], '/') == NULL && i > 2)
			ft_error_cmd(cmd_path[0]);
		else
			ft_error_file_directory(cmd_path[0]);
		free_split(cmd_path);
		exit(127);
	}
	if (access(cmd_path[0], X_OK) == ERROR)
	{
		if (i == 2 || i == 1)
			ft_error_permission_envp(cmd_path[0]);
		else
			ft_error_permission(cmd_path[0]);
		free_split(cmd_path);
		exit(126);
	}
	else
		return (SUCCESS);
}
