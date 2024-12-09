/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/07 00:42:59 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void put_lst_envp(t_envp *envp)
{
    t_envp *current = envp;
    while (current)
    {
        printf("%s%s\n", current->name, current->value);
        current = current->next;
    }
}

void put_tab_env(char **env)
{
    int i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

	// put_lst_envp(data.envp.envp);
	// put_tab_env(data.envp.env);


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	pars_env(&data, env);
	while (1)
	{
		if (handle_prompt(&data) == ERROR)
			return (2);
		pars_shell(&data, argc, argv);
		// exec_command(data);
		//free_token_list(data);
		free(data.prompt.read_line);
		ft_memset(&data, 0, sizeof(t_data));
	}
	return (0);
}
