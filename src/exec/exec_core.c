/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/15 01:48:09 by rbalazs          ###   ########.fr       */
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
	free(path);
	if (data->envc && data->envc[0] && data->envc[1] && data->envc[2])
	{
		if (!data->envc[i])
			ft_close_fd(data, "Error: no path\n");
		dir_path = ft_split(data->envc[i] + 5, ':');
	}
	else
	{
		path = ft_strdup("/usr/bin/");
		if (!path)
			ft_close_fd(data, "Error: strdup failed\n");
		dir_path = ft_split(path, ':');
		free(path);
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

	if (!data->envc)
		ft_close_fd(data, "Error: no env\n");
	dir_path = get_dir_path(data);
	i = -1;
	while (dir_path[++i])
	{
		join_path = ft_strjoin(dir_path[i], "/");
		if (!join_path)
			ft_close_fd(data, "Error: strjoin failed\n");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (!path)
			ft_close_fd(data, "Error: strjoin failed\n");
		if (access(path, F_OK) == 0)
			return (ft_free_tab(dir_path), path);
		free(path);
	}
	ft_free_tab(dir_path);
	return (NULL);
}

void	exec_minishell(t_data *data, char **cmd)
{
	char	*path;
	char	*cmd_minishell;

	path = getcwd(NULL, 0);
	cmd_minishell = ft_strjoin(path, "/minishell");
	change_shlvl(data);
	copy_env_char(data);
	if (execve(cmd_minishell, cmd, data->envc) == -1)
	{
		free(path);
		free(cmd_minishell);
		ft_close_fd(data, "execve fail\n");
	}
}

void	exec(t_data *data, char **cmd)
{
	char	*path;

	if (!cmd || !cmd[0])
		ft_close_fd(data, "Error: no command\n");
	if (!data->envc)
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
		ft_close_fd(data, ": command not found\n");
	}
	if (execve(path, cmd, data->envc) == -1)
		ft_close_fd(data, "execve fail\n");
}
