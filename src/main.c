/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/13 01:53:15 by sben-tay         ###   ########.fr       */
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

void put_lst_redir(t_data	*param)
{
    t_redir_manag	*current = param->token_manag.token->redir_in;
	printf("%p\n", current);
	if (!current)
	{
		printf("current = NULL\n");
	}
	printf("filename[%s] type[%s]\n", current->head->file_name, current->head->type);
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
		if (pars_shell(&data, argc, argv) == ERROR)
		{
			// JE DOIS PAS LANCER LE LEXEUR ET L EXEC
		}
		// put_lst_redir(&data);
		// exec_command(data);
		//free_token_list(data);
		free(data.prompt.read_line);
		ft_memset(&data, 0, sizeof(t_data));
	}
	return (0);
}
