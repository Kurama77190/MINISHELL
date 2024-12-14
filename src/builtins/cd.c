/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/13 13:14:29 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_oldpwd(char *old_pwd, t_data *data)
{
	t_env	*current;
	char	*new_line;

	if (!old_pwd || !data->env || !data->env->name)
		return ;
	current = data->env;
	while (current)
	{
		if (!ft_strncmp(current->name, "OLDPWD", 6))
		{
			free(current->line);
			current->line = NULL;
			free(current->value);
			current->value = NULL;
			free(current->name);
			current->name = NULL;
			new_line = ft_strjoin("OLDPWD=", old_pwd);
			current->line = new_line;
			current->value = ft_strdup(old_pwd);
		}
		current = current->next;
	}
}

void	set_env_pwd(char *new_pwd, t_data *data)
{
	t_env	*current;
	char	*new_line;
	char	*old_pwd;

	if (!new_pwd || !data->env || !data->env->name)
		return ;
	current = data->env;
	while (current)
	{
		if (!ft_strncmp(current->name, "PWD", 3))
		{
			if (current->value)
			{
				old_pwd = ft_strdup(current->value);
				free(current->value);
				current->value = NULL;
			}
			if (current->line)
				free(current->line);
			current->line = NULL;
			if (current->name)
				free(current->name);
			current->name = NULL;
			new_line = ft_strjoin("PWD=", new_pwd);
			current->line = new_line;
			current->value = ft_strdup(new_pwd);
		}
		current = current->next;
		if (old_pwd)
		{
			set_env_oldpwd(old_pwd, data);
			free(old_pwd);
			old_pwd = NULL;
		}
	}
}

void	ft_move_directory(char *path, t_data *data)
{
	char	*new_pwd;

	if (!path)
		return ;
	if (chdir(path) != 0)
		ft_putstr_fd("cd: no such file or directory: \n", 2);
	new_pwd = getcwd(NULL, 0);
	set_env_pwd(new_pwd, data);
	free(new_pwd);
}

void	set_home(t_data *data)
{
	t_env	*current;

	if (!data->env)
		return ;
	current = data->env;
	while (current)
	{
		if (!ft_strncmp(current->name, "HOME", 4))
			ft_move_directory(current->value, data);
		current = current->next;
	}
}

void	ft_cd(char **argv, t_data *data)
{
	if (!data->env)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		data->exit_status = 1;
		return ;
	}
	if (argv[1] == NULL)
		set_home(data);
	else if (argv[1] != NULL && argv[2] == NULL)
		ft_move_directory(argv[1], data);
	else
	{
		ft_putstr_fd("cd: too many arguments\n", 1);
		data->exit_status = 1;
	}
	data->exit_status = 0;
}
