/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:21 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/19 16:14:23 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Error PWD");
		data->exit_status = 1;
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		free(pwd);
	}
	data->exit_status = 0;
}
