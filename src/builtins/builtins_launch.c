/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_launch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:31:17 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 19:31:20 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_detect_builtin(char **argv, t_data *data)
{
	if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, data);
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv, data);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(argv, data);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argv, data);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(argv, data);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv, data);
	else
		return (false);
	return (true);
}
