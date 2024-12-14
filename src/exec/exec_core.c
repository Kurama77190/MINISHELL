/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/13 18:24:42 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_path(char *cmd, t_data *data)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;
	char	*path_to_find;
	int		len;
	char	*path2;

	if (!data->envc)
		ft_close_fd(data, "Error: no env\n");
	i = 0;
	len = 0;
	while (data->envc[len])
		len++;
	if (len <= 3)
		path_to_find = ft_strdup("_");
	else
		path_to_find = ft_strdup("PATH");
	while (data->envc[i] && ft_strnstr(data->envc[i], path_to_find, 4) == 0)
		i++;
	free(path_to_find);
	if (len <= 3)
	{
		path2 = ft_strdup("/usr/bin/");
		if (!path2)
			ft_close_fd(data, "Error: strdup failed\n");
		dir_path = ft_split(path2, ':');
		free(path2);
	}
	else
	{
		if (!data->envc[i])
			ft_close_fd(data, "Error: no path\n");
		dir_path = ft_split(data->envc[i] + 5, ':');
	}
	if (!dir_path)
		ft_close_fd(data, "Error: split failed\n");
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

void	change_shlvl(t_data *data)
{
	t_env	*tmp;
	char	*shlvl;
	int		lvl_int;

	lvl_int = 0;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, "SHLVL=", 6) == 0)
		{
			shlvl = ft_substr(tmp->line, 6, ft_strlen(tmp->line) - 6);
			lvl_int = ft_atoi(shlvl);
			free(shlvl);
			break ;
		}
		tmp = tmp->next;
	}
	if (lvl_int == 0)
	{
		push_node_to_env(data, "SHLVL=1");
		return ;
	}
	lvl_int++;
	shlvl = ft_itoa(lvl_int);
	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, "SHLVL=", 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(shlvl);
			free(tmp->line);
			tmp->line = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			break ;
		}
		tmp = tmp->next;
	}
}

void	exec(t_data *data, char **cmd)
{
	char	*path;
	char	*cmd_minishell;

	if (!cmd || !cmd[0])
		ft_close_fd(data, "Error: no command\n");
	if (!data->envc)
		ft_close_fd(data, "Error: no env\n");
	if (ft_strncmp(cmd[0], "./minishell", 11) == 0)
	{
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
