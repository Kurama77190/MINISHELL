/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/19 19:01:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// void	exec_minishell(t_data *data, char **cmd)
// {
// 	char	*path;
// 	char	*cmd_minishell;

// 	path = getcwd(NULL, 0);
// 	cmd_minishell = ft_strjoin(path, "/minishell");
// 	change_shlvl(data);
// 	uptdate_env(data);
// 	if (execve(cmd_minishell, cmd, data->e.env) == -1)
// 	{
// 		ft_free((void **)&path);
// 		ft_free((void **)&cmd_minishell);
// 		ft_close_fd(data, "execve fail\n");
// 	}
// }

void	exec(t_data *data, char **cmd)
{
		
	if (execve(path, cmd, data->e.env) == -1)
	{
		ft_free_all_child(data);
		ft_close_fd(data, "execve fail\n");
	}
}
