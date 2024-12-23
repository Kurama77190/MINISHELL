/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:11:14 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/23 23:27:16 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

// void	put_lst_envp(t_envp *envp)
// {
// 	t_envp	*current;

// 	current = envp;
// 	while (current)
// 	{
// 		printf("%s\n", current->name);
// 		// printf("%s%s\n", current->name, current->value);
// 		current = current->next;
// 	}
// }

// void	put_tab_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }

// put_lst_envp(data.envp.envp);
// put_tab_env(data.envp.env);

// printf("intfile[%s] type[%s]\n", new->redir_in->head->file_name,
	//new->redir_in->head->type);
// printf("outfile[%s] type[%s]\n", new->redir_out->head->file_name,
	//new->redir_out->head->type);

// void	put_tokenizer_data(t_data *data)
// {
// 	t_token	*current;
// 	t_redir	*redir;
// 	int		j;
// 	int		i;

// 	i = 1;
// 	current = data->token_manag.token;
// 	while (current)
// 	{
// 		printf("\n\033[1;34m[Token Data %i]\033[0m\n", i);
// 		printf("\033[1;33mCommand:\033[0m %s\n", current->command);
// 		printf("\033[1;33mArguments:\033[0m");
// 		if (current->args)
// 		{
// 			j = 0;
// 			while (current->args[j])
// 			{
// 				printf(" [%s]", current->args[j]);
// 				j++;
// 			}
// 		}
// 		else
// 			printf(" None");
// 		printf("\n");
// 		redir = current->redir_in.head;
// 		while (redir)
// 		{
// 			printf("\033[1;32mRedir In:\033[0m File: %s, Type: %s\n",
// 				redir->file_name, redir->type);
// 			redir = redir->next;
// 		}
// 		redir = current->redir_out.head;
// 		while (redir)
// 		{
// 			printf("\033[1;31mRedir Out:\033[0m File: %s, Type: %s\n",
// 				redir->file_name, redir->type);
// 			redir = redir->next;
// 		}
// 		current = current->next;
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	pars_env(&data, env);
	while (1)
	{
		signals();
		handle_prompt(&data);
		if (pars_shell(&data, argc, argv) != ERROR)
		{
			ft_execution(&data);
			pid_controller(&data);
		}
		// put_tokenizer_data(&data);
		ft_free_all(&data, false);
		ft_memory(&data);
	}
	return (0);
}
