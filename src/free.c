#include "minishell.h"

// void	free_redir(t_redir **redir)
// {
// 	t_redir	*next;
// 	t_redir	*tmp;

// 	if (!redir)
// 		return ;
// 	tmp = *redir;
// 	while (tmp)
// 	{
// 		if (tmp->value)
// 			free(tmp->value);
// 		tmp->value = NULL;
// 		if (tmp->file_here_doc)
// 			free(tmp->file_here_doc);
// 		tmp->file_here_doc = NULL;
// 		next = tmp->next;
// 		if (tmp)
// 			free(tmp);
// 		tmp = next;
// 	}
// 	*redir = NULL;
// }

// void	ft_free_redir_list(t_redir *head)
// {
// 	t_redir	*next;

// 	while (head)
// 	{
// 		next = head->next;
// 		if (head->value)
// 			free(head->value);
// 		head->value = NULL;
// 		if (head->file_here_doc)
// 			free(head->file_here_doc);
// 		head->file_here_doc = NULL;
// 		free(head);
// 		head = next;
// 	}
// }

// void	ft_free_shell_list(t_shell_list *shell_list)
// {
// 	t_shell_list	*tmp;

// 	if (!shell_list)
// 		return ;
// 	while (shell_list)
// 	{
// 		tmp = shell_list;
// 		shell_list = shell_list->next;
// 		if (tmp->command != NULL)
// 		{
// 			free(tmp->command);
// 			tmp->command = NULL;
// 		}
// 		if (tmp->argv)
// 			ft_free_tab(tmp->argv);
// 		if (tmp->redir)
// 			ft_free_redir_list(tmp->redir);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// }

// void	ft_free_command(t_ast_node *node)
// {
// 	if (!node)
// 		return ;
// 	free_redir(&node->redir);
// 	free(node->command);
// 	ft_free_tab(node->argv);
// }

// void	free_node(t_ast_node *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_CMD)
// 		ft_free_command(node);
// 	else
// 	{
// 		if (node->left)
// 			free_node(node->left);
// 		if (node->right)
// 			free_node(node->right);
// 	}
// 	free(node);
// }

// void	free_ast(t_ast_node **node, t_data *data)
// {
// 	free_node(*node);
// 	*node = NULL;
// 	if (data->tok)
// 		ft_stackclear(&data->tok);
// }

// void	ft_free_all_redirs(t_shell_list *shell_list)
// {
// 	t_shell_list	*current;

// 	current = shell_list;
// 	while (current)
// 	{
// 		ft_free_redir_list(current->redir);
// 		current->redir = NULL;
// 		current = current->next;
// 	}
// }

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->prompt.read_line)
		ft_free((void **)&data->prompt.read_line);
	// if (data->token_manag.token)
	// 	ft_free_token_list(&data->token_manag.token);
	if (data->e.env)
	{
		ft_free_tab(data->e.env);
		data->e.envp = NULL;
	}
	if (data->free_value == 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		// if (data->env)
		// {
		// 	ft_envclear(data->env);
		// 	data->env = NULL;
		// }
	}
}
