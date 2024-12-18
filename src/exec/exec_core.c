/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/18 03:09:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_dir_path(t_data *data)
{
	char	**dir_path;
	char	*path;
	int		i;

	i = 0;
	path = find_path_to_find(data);
	search_index(data, &i, path);
	ft_free((void **)&path);
	if (data->e.env && data->e.env[0] && data->e.env[1] && data->e.env[2])
	{
		if (!data->e.env[i])
			ft_close_fd(data, "Error: no path\n");
		dir_path = ft_split(data->e.env[i] + 5, ':');
		if (!dir_path)
			return (NULL);
	}
	else
	{
		path = ft_strdup("/usr/bin/");
		if (!path)
			ft_close_fd(data, "Error: strdup failed\n");
		dir_path = ft_split(path, ':');
		ft_free((void **)&path);
	}
	if (!dir_path)
		ft_close_fd(data, "Error: split failed\n");
	return (dir_path);
}

char	*ft_path(char *cmd, t_data *data)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	if (!data->e.env)
		ft_close_fd(data, "Error: no env\n");
	dir_path = get_dir_path(data);
	i = -1;
	while (dir_path[++i])
	{
		join_path = ft_strjoin(dir_path[i], "/");
		if (!join_path)
			ft_close_fd(data, "Error: strjoin failed\n");
		path = ft_strjoin(join_path, cmd);
		ft_free((void **)&join_path);
		if (!path)
			ft_close_fd(data, "Error: strjoin failed\n");
		if (access(path, F_OK) == 0)
			return (free_split(dir_path), path);
		ft_free((void **)&path);
	}
	free_split(dir_path);
	return (NULL);
}

void	exec_minishell(t_data *data, char **cmd)
{
	char	*path;
	char	*cmd_minishell;

	path = getcwd(NULL, 0);
	cmd_minishell = ft_strjoin(path, "/minishell");
	change_shlvl(data);
	uptdate_env(data);
	if (execve(cmd_minishell, cmd, data->e.env) == -1)
	{
		ft_free((void **)&path);
		ft_free((void **)&cmd_minishell);
		ft_close_fd(data, "execve fail\n");
	}
}

void	exec(t_data *data, char **cmd)
{
	char	*path;

	if (!data->e.env)
		ft_close_fd(data, "Error: no env\n");
	if (ft_strncmp(cmd[0], "./minishell", 11) == 0)
	{
		exec_minishell(data, cmd);
		return ;
	}
	path = ft_path(cmd[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	if (execve(path, cmd, data->e.env) == -1)
	{
		ft_free_all_child(data);
		ft_close_fd(data, "execve fail\n");
	}
}
