/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:31:17 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/22 12:34:35 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_detect_builtin(char **argv, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(argv[0], "cd"))
		exit_code = ft_cd(argv, data);
	else if (!ft_strcmp(argv[0], "echo"))
		exit_code = ft_echo(argv, data);
	else if (!ft_strcmp(argv[0], "pwd"))
		exit_code = ft_pwd(data);
	else if (!ft_strcmp(argv[0], "export"))
		exit_code = ft_export(argv, data);
	else if (!ft_strcmp(argv[0], "unset"))
		exit_code = ft_unset(argv, data);
	else if (!ft_strcmp(argv[0], "env"))
		exit_code = ft_env(argv, data);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv, data);
	else
		return (0);
	return (exit_code);
}
