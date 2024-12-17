/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:15:22 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 12:34:01 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_to_find(t_data *data)
{
	if (data->e.env && data->e.env[0] && data->e.env[1] && data->e.env[2])
		return (ft_strdup("PATH"));
	else
		return (ft_strdup("_"));
}

void	search_index(t_data *data, int *i, char *path)
{
	while (data->e.env[*i] && ft_strnstr(data->e.env[*i], path, 4) == 0)
		(*i)++;
}

// void	increment_shlvl(t_data *data, int lvl_int)
// {
// 	t_env	*tmp;
// 	char	*shlvl;

// 	lvl_int++;
// 	shlvl = ft_itoa(lvl_int);
// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->line, "SHLVL=", 6) == 0)
// 		{
// 			ft_free((void**)&tmp->value);
// 			tmp->value = ft_strdup(shlvl);
// 			ft_free((void**)&tmp->line);
// 			tmp->line = ft_strjoin("SHLVL=", shlvl);
// 			ft_free((void**)&shlvl);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	change_shlvl(t_data *data)
// {
// 	t_env	*tmp;
// 	char	*shlvl;
// 	int		lvl_int;

// 	lvl_int = 0;
// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->line, "SHLVL=", 6) == 0)
// 		{
// 			shlvl = ft_substr(tmp->line, 6, ft_strlen(tmp->line) - 6);
// 			lvl_int = ft_atoi(shlvl);
// 			ft_free((void**)&shlvl);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (lvl_int == 0)
// 	{
// 		push_node_to_env(data, "SHLVL=1");
// 		return ;
// 	}
// 	increment_shlvl(data, lvl_int);
// }
