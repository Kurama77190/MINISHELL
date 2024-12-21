/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:12 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/21 08:25:51 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_name(char *line)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*put_value(char *line)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (!line[i])
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(line) - i));
	if (!res)
		return (NULL);
	i++;
	while (line[i])
	{
		res[j] = line[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_envp	*new_node_env(char *line, t_data *data)
{
	t_envp	*new_node;

	if (!line)
		return (NULL);
	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->line = ft_strdup(line);
	if (!new_node->line)
	{
		free(new_node);
		ft_error(data, "Malloc failed\n");
		return (NULL);
	}
	new_node->name = put_name(line);
	new_node->value = put_value(line);
	new_node->next = NULL;
	return (new_node);
}

void	push_node_to_env(t_data *data, char *env_line)
{
	t_envp	*new_node;
	t_envp	*current;

	new_node = new_node_env(env_line, data);
	if (!new_node)
		return ;
	current = data->e.envp;
	if (data->e.envp == NULL)
		data->e.envp = new_node;
	else
	{
		current = data->e.envp;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_env(char **argv, t_data *data)
{
	t_envp	*current;

	current = data->e.envp;
	if (argv[1] && ft_strcmp(argv[1], "env"))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 127;
		return ;
	}
	while (current != NULL)
	{
		if (current->value)
		{
			ft_putstr_fd(current->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
	data->exit_status = 0;
}
