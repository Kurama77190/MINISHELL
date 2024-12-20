/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:55:41 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/19 18:16:18 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// LAST FOLDER FOR STORING THE FUNCTIONS RELATED TO THE PATH

static int	checker_access(char *cmd_path, char **commands, char **path_env);
static void	ft_check_cmd_infile(t_data *data, char **commands);
static void	ft_error_split(t_data *data);

/* **************************** */
/*  🌟 SEARCH_PATH_IN_ENVP 🌟  */
/* **************************** */

char	**get_path(t_data *data)
{
	int		i;
	char	*env;
	char	**path_;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH", 4) == SUCCESS)
		{
			env = data->envp[i] + 5;
			break ;
		}
		i++;
	}
	if (data->envp[i] == NULL)
		return (NULL);
	else
		path_ = ft_split_envp(env, ':');
	if (path_ == NULL)
		return (NULL);
	return (path_);
}
/* ****************************************** */
/*  🌟 SEARCH_PATH_CMD_IN_ENVP_OR_INFILE 🌟  */
/* ****************************************** */

char	*get_cmd(t_data *data, int i)
{
	char	**path_env;
	char	*cmd_path;
	char	**commands;
	int		index_tab;

	index_tab = 0;
	commands = ft_split(data->argv[i], ' ');
	if (!commands)
		ft_error_split(data);
	path_env = get_path(data);
	if (path_env == NULL)
		ft_check_cmd_infile(data, commands);
	while (path_env[index_tab])
	{
		cmd_path = ft_strjoin(path_env[index_tab], commands[0]);
		if (checker_access(cmd_path, commands, path_env) == SUCCESS)
			return (cmd_path);
		index_tab++;
		free(cmd_path);
	}
	ft_error_cmd(commands[0]);
	free_split(commands);
	free_split(path_env);
	return (NULL);
}

/* **************** */
/*  🌟 HELPERS 🌟  */
/* **************** */

static int	checker_access(char *cmd_path, char **commands, char **path_env)
{
	if (access(cmd_path, F_OK) == SUCCESS)
	{
		if (access(cmd_path, X_OK) == ERROR)
		{
			ft_error_permission(commands[0]);
			free(cmd_path);
			free_split(commands);
			free_split(path_env);
			exit(126);
		}
		free_split(commands);
		free_split(path_env);
		return (SUCCESS);
	}
	else
		return (ERROR);
}

static void	ft_check_cmd_infile(t_data *data, char **commands)
{
	char	*tmp;

	tmp = ft_strjoin("./", commands[0]);
	if (access(tmp, F_OK) == ERROR)
	{
		ft_error_file_directory(commands[0]);
		free(tmp);
		free_split(commands);
		exit(127);
	}
	if (access(tmp, X_OK) == ERROR)
	{
		ft_error_permission(commands[0]);
		free(tmp);
		free_split(commands);
		exit(126);
	}
	else
		execve(tmp, commands, data->envp);
}

static void	ft_error_split(t_data *data)
{
	if (data->cmd)
		free_split(data->cmd);
	exit(1);
}
