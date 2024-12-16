/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/16 04:31:41 by sben-tay         ###   ########.fr       */
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

	// printf("intfile[%s] type[%s]\n", new->redir_in->head->file_name, new->redir_in->head->type);
	// printf("outfile[%s] type[%s]\n", new->redir_out->head->file_name, new->redir_out->head->type);

void	put_tokenizer_data(t_data *data)
{
	t_token	*current = data->token_manag.token;
	int i = 0;
	while (current)
	{
		printf("\033[37mtokenizer\033[33m[%i]\033[0m\n", i);
		while (current->redir_in.head)
		{
			printf("\033[37mredir_in\033[0m\033[33m[%s]\033[0m type\033[33m[%s]\033[0m\n", current->redir_in.head->file_name, current->redir_in.head->type);
			current->redir_in.head = current->redir_in.head->next;
			printf("%p", current->redir_in.head);
		}
		while (current->redir_out.head)
		{
			printf("redir_out[%s] type[%s]\n", current->redir_out.head->file_name, current->redir_out.head->type);
			current->redir_out.head = current->redir_out.head->next;
			printf("%p\n", current->redir_out.head);
		}
		printf("commands[%s]\033[0m\n",current->command);
		// int	j = 0;
		printf("args[%p] ", current->args);
		// while(current->args[j])
		// {
		// 	j++;
		// }
		// printf("]\n");
		i++;
		current = current->next;
	}
}


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
		if (pars_shell(&data, argc, argv) != ERROR)
		{
		// exec_command(data);
		}
		// free_token_list(data);
		put_tokenizer_data(&data);
		free(data.prompt.read_line);
		ft_memset(&data, 0, sizeof(t_data));
	}
	return (0);
}

// "|     > in1" ceci est une commande!