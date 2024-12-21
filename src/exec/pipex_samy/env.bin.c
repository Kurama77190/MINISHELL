/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 04:42:26 by samy              #+#    #+#             */
/*   Updated: 2024/12/21 04:58:12 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_env_bin(t_data *data)
{
	char	**env;

	env = ft_calloc(1024, sizeof(char *));
	if (!env)
	{
		perror("bash: calloc: ");
		ft_free_all(data, true);
		return (NULL);
	}
	env[0] = ft_strdup("/bin:/usr/bin");
	env[1] = NULL;
	return (env);
}