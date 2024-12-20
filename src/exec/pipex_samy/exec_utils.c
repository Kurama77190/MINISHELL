/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:58:46 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/19 18:15:19 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ********************************************** */
/*  🌟 CHECKER_ACCESS_WITHOUT_ENVP_NOT_EXIST 🌟  */
/* ********************************************** */

int	ft_check_access_bin_without_envp(char *cmd_path, int i, t_data *data)
{
	if (access(cmd_path, F_OK) == ERROR)
	{
		if (i == 2 || i == 1)
			ft_error_cmd_envp(data->cmd[0]);
		else if (ft_strchr(cmd_path, '/') == NULL && i > 2)
			ft_error_cmd(data->cmd[0]);
		else
			ft_error_file_directory(data->cmd[0]);
		free(cmd_path);
		free_split(data->cmd);
		exit(127);
	}
	if (access(cmd_path, X_OK) == ERROR)
	{
		if (i == 2 || i == 1)
			ft_error_permission_envp(data->cmd[0]);
		else
			ft_error_permission(data->cmd[0]);
		free(cmd_path);
		free_split(data->cmd);
		exit(126);
	}
	else
		return (SUCCESS);
}
