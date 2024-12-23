/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:45:06 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 18:19:23 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ****************** */
/*  🌟 MSG_ERROR 🌟  */
/* ****************** */

int	ft_error_msg(char *msg_error)
{
	ft_dprintf(2, "bash: %s: %s\n", msg_error, strerror(errno));
	return (ERROR);
}

void	ft_error_cmd(char *cmd)
{
	char	*tmp;
	char	*msg;

	tmp = ft_strjoin("bash: ", cmd);
	if (!tmp)
		return ;
	msg = ft_strjoin(tmp, ": command not found\n");
	if (!msg)
	{
		ft_free((void **)&tmp);
		return ;
	}
	ft_putstr_fd(msg, 2);
	ft_free((void **)&tmp);
	ft_free((void **)&msg);
}

void	ft_error_permission(char *cmd)
{
	char	**tmp;

	if (ft_strchr(cmd, ' ') != NULL)
	{
		tmp = ft_split(cmd, ' ');
		if (!cmd)
			return ;
		ft_dprintf(2, "bash: %s: Permission denied\n", tmp[0]);
	}
	else
		ft_dprintf(2, "bash: %s: Permission denied\n", cmd);
}

void	ft_error_file_directory(char *cmd)
{
	char	*tmp;
	char	*msg;

	tmp = ft_strjoin("bash: ", cmd);
	if (!tmp)
		return ;
	msg = ft_strjoin(tmp, ": No such file or directory\n");
	if (!msg)
	{
		ft_free((void **)&tmp);
		return ;
	}
	ft_putstr_fd(msg, 2);
	ft_free((void **)&tmp);
	ft_free((void **)&msg);
}
