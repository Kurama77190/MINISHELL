/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:55:41 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 21:43:33 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* **************************** */
/*  🌟 SEARCH_PATH_IN_ENVP 🌟  */
/* **************************** */

char	**get_path(t_data *data)
{
	int		i;
	char	*env;
	char	**path_;

	i = 0;
	while (data->e.env[i])
	{
		if (ft_strncmp(data->e.env[i], "PATH", 4) == SUCCESS)
		{
			env = data->e.env[i] + 5;
			break ;
		}
		i++;
	}
	if (data->e.env[i] == NULL)
		return (NULL);
	else
		path_ = ft_split_envp(env, ':');
	if (path_ == NULL)
		return (NULL);
	return (path_);
}
/* **************** */
/*  🌟 HELPERS 🌟  */
/* **************** */

static int	checker_access(t_data *data, char *cmd_path, t_token *token, \
							char **path_env)
{
	if (access(cmd_path, F_OK) != -1)
	{
		if (access(cmd_path, X_OK) == -1)
		{
			ft_error_permission(token->args[0]);
			ft_free((void **)&cmd_path);
			free_split(path_env);
			ft_free_all(data, true);
			exit(126);
		}
		return (SUCCESS);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

static void	ft_check_cmd_infile(t_data *data, t_token *token)
{
	char	*tmp;

	tmp = ft_strjoin("./", token->args[0]);
	if (access(tmp, F_OK) == -1)
	{
		ft_error_file_directory(token->args[0]);
		ft_free((void **)&tmp);
		ft_free_all(data, true);
		exit(127);
	}
	if (access(tmp, X_OK) == -1)
	{
		ft_error_permission(token->args[0]);
		ft_free((void **)&tmp);
		ft_free_all(data, true);
		exit(126);
	}
	else
		execve(tmp, token->args, data->e.env);
}

/* ****************************************** */
/*  🌟 SEARCH_PATH_CMD_IN_ENVP_OR_INFILE 🌟  */
/* ****************************************** */

char	*get_cmd(t_data *data, t_token *token)
{
	char	*cmd_path;
	int		index_tab;

	index_tab = 0;
	data->path_env = get_path(data);
	if (data->path_env == NULL)
		ft_check_cmd_infile(data, token);
	while (data->path_env[index_tab])
	{
		cmd_path = ft_strjoin(data->path_env[index_tab], token->args[0]);
		if (checker_access(data, cmd_path, token, data->path_env) == SUCCESS)
		{
			return (cmd_path);
		}
		index_tab++;
		ft_free((void **)&cmd_path);
	}
	ft_error_cmd(token->args[0]);
	ft_free((void **)&cmd_path);
	ft_free_all(data, true);
	exit(127);
	return (NULL);
}
