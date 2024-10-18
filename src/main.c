/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/10/18 22:12:46 by sben-tay         ###   ########.fr       */
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



int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	// printf("wqerwqerwqerqwerqwerqwe\n");
	if (pars_shell(&data, argc, argv, env) == ERROR)
	{
		ft_putstr_fd("exit\n", 2);
		return (2);
	}
	// put_tab_env(data.envp.env);
	// printf("%p\n", data.envp.envp);
	put_lst_envp(data.envp.envp);
	return (0);
	while (1)
	{
		data.prompt.read_line = readline("minishell-1.0$ ");
		if (!data.prompt.read_line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*(data.prompt.read_line))
		{
			add_history(data.prompt.read_line);
		}
		
		// exec_command(data);
		
		//free_token_list(data);

		free(data.prompt.read_line);
		// free token;
		ft_memset(&data, 0, sizeof(t_data));
	}
	return (0);
}