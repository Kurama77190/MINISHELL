/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_without_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:46:31 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/21 10:07:44 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_in_bin(t_data *data, t_token *token);
int	ft_exec_absolut_path_cmd_without_envp(t_data *data, t_token *token);
int	ft_check_access_without_envp(t_data *data, char **cmd_path);
int	ft_check_access_bin_without_envp(t_data *data, char	*tmp_cmd, \
	t_token *token);

/* ************************** */
/*  🌟 EXEC_WITHOUT_ENVP 🌟  */
/* ************************** */

int	ft_exec_without_envp_set(t_data *data, t_token *token)
{
	if (ft_strchr(token->args[0], '/') != NULL)
	{
		if (ft_exec_absolut_path_cmd_without_envp(data, token) == ERROR)
			return (ERROR);
	}
	if (ft_strchr(token->args[0], '/') == NULL)
	{
		if (ft_exec_in_bin(data, token) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/* ******************************* */
/*  🌟 EXEC_COMMANDS_BIN_ONLY 🌟  */
/* ******************************* */

int	ft_exec_in_bin(t_data *data, t_token *token)
{
	char	*cmd_tmp;
	char	**env_tmp;

	cmd_tmp = ft_strjoin("/bin/", token->args[0]);
	if (!cmd_tmp)
		return (ERROR);
	env_tmp = set_env_bin(data);
	if (!env_tmp)
	{
		free(cmd_tmp);
		return (ERROR);
	}
	if (ft_check_access_bin_without_envp(data, cmd_tmp, token) == SUCCESS)
	{
		if (execve(token->args[0], token->args, data->e.env) == ERROR)
		{
			ft_free((void **)&cmd_tmp);
			ft_free((void **)&env_tmp);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/* ********************************************* */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH_WHITOUT_ENV 🌟  */
/* ********************************************* */

int	ft_exec_absolut_path_cmd_without_envp(t_data *data, t_token *token)
{
	if (ft_check_access_without_envp(data, token->args) == SUCCESS)
	{
		if (execve(token->args[0], token->args, data->e.env) == ERROR)
		{
			ft_error_msg("execve");
			ft_free_all(data, true);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/* **************************************************** */
/*  🌟 EXECVE_WITH_ABSOLUT_PATH_WHITOUT_ENV_HELPER 🌟  */
/* **************************************************** */

int	ft_check_access_without_envp(t_data *data, char **cmd_path)
{
	if (access(cmd_path[0], F_OK) == -1)
	{
		if (!ft_strchr(cmd_path[0], '/'))
			ft_error_cmd(cmd_path[0]);
		else
			ft_error_file_directory(cmd_path[0]);
		ft_free_all(data, true);
		exit(127);
	}
	if (access(cmd_path[0], X_OK) == -1)
	{
		ft_error_permission(cmd_path[0]);
		ft_free_all(data, true);
		exit(126);
	}
	else
		return (SUCCESS);
}

int	ft_check_access_bin_without_envp(t_data *data, char	*tmp_cmd, \
									t_token *token)
{
	if (access(tmp_cmd, F_OK) == -1)
	{
		if (ft_strchr(tmp_cmd, '/') == NULL)
			ft_error_cmd(token->args[0]);
		else
			ft_error_file_directory(token->args[0]);
		ft_free((void **)&tmp_cmd);
		ft_free_all(data, true);
		exit(127);
	}
	if (access(tmp_cmd, X_OK) == -1)
	{
		ft_error_permission(token->args[0]);
		ft_free((void **)&tmp_cmd);
		ft_free_all(data, true);
		exit(126);
	}
	else
		return (SUCCESS);
}
