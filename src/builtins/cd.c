/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/21 05:13:54 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_oldpwd(char *old_pwd, t_data *data)
{
	t_envp	*current;
	char	*new_line;

	if (!old_pwd || !data->e.envp || !data->e.envp->name)
		return ;
	current = data->e.envp;
	while (current)
	{
		if (current->name && !ft_strncmp(current->name, "OLDPWD", 6))
		{
			if (current->line)
				ft_free((void **)&current->line);
			if (current->value)
				ft_free((void **)&current->value);
			if (old_pwd)
				new_line = ft_strjoin("OLDPWD=", old_pwd);
			current->line = new_line;
			ft_free((void **)&current->name);
			current->name = ft_strdup("OLDPWD");
			ft_free((void **)&current->value);
			current->value = ft_strdup(old_pwd);
		}
		current = current->next;
	}
}

void	update_pwd_value(t_envp *current, char *new_pwd, char **old_pwd)
{
	if (current->value)
	{
		*old_pwd = ft_strdup(current->value);
		ft_free((void **)&current->value);
	}
	if (current->line)
		ft_free((void **)&current->line);
	if (current->name)
		ft_free((void **)&current->name);
	current->line = ft_strjoin("PWD=", new_pwd);
	current->name = ft_strdup("PWD");
	current->value = ft_strdup(new_pwd);
}

void	set_env_pwd(char *new_pwd, t_data *data)
{
	t_envp	*current;
	char	*old_pwd;

	if (!new_pwd || !data->e.envp || !data->e.envp->name)
		return ;
	old_pwd = NULL;
	current = data->e.envp;
	while (current)
	{
		if (current->name && !ft_strncmp(current->name, "PWD", 3))
			update_pwd_value(current, new_pwd, &old_pwd);
		current = current->next;
		if (old_pwd)
		{
			set_env_oldpwd(old_pwd, data);
			ft_free((void **)&old_pwd);
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
	ft_free((void **)&new_pwd);
}

void	ft_cd(char **argv, t_data *data)
{
	if (!data->e.envp)
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
