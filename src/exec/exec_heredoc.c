/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:12:35 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/23 19:58:28 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_filename(t_redir *redir)
{
	char	*temp_file;
	char	*temp_num;

	temp_num = ft_itoa(getpid() + 1);
	temp_file = ft_strjoin("./minishell_heredoc_", temp_num);
	ft_free((void **)&temp_num);
	if (!temp_file)
	{
		perror("ft_strjoin");
		ft_free((void **)&temp_file);
		return ;
	}
	if (access(temp_file, F_OK) == -1)
	{
		redir->file_here_doc = ft_strdup(temp_file);
		ft_free((void **)&temp_file);
		return ;
	}
	redir->file_here_doc = ft_strdup(temp_file);
	ft_free((void **)&temp_file);
}

int	rl_event_dummy(void);

static int	execute_here_doc(t_redir *redir, t_data *data, char *file_path, \
		int file)
{
	char	*line;
	int		count;

	(void)file_path;
	count = 0;
	signal(SIGINT, heredoc_sigint_handler);
	data->exit_status = 0;
	rl_event_hook = rl_event_dummy;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(redir->file_name, line))
			break ;
		else
			ft_putendl_fd(line, file);
		count++;
		if (g_exit_status == SIGINT || !ft_strcmp(line, redir->file_name))
		{
			ft_free((void **)&line);
			if (g_exit_status == SIGINT)
				return (close(file), data->exit_status = 128 + SIGINT, ERROR);
			break ;
		}
	}
	return (SUCCESS);
}

int	ft_process_heredoc(t_redir *redir, t_data *data)
{
	char	*file_path;
	int		file;

	file = -1;
	create_filename(redir);
	if (!redir && !redir->file_here_doc)
		return (ERROR);
	file_path = redir->file_here_doc;
	file = open(file_path, O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (file == -1)
		perror("heredoc");
	while (*file_path)
		file_path++;
	if (execute_here_doc(redir, data, file_path, file) == ERROR)
		return (ERROR);
	close(file);
	return (SUCCESS);
}
