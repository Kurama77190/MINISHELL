/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:12:35 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/18 22:28:42 by sben-tay         ###   ########.fr       */
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

static void	execute_here_doc(t_redir *redir, t_data *data, char *file_path,
		int file)
{
	(void)data;
	(void)file_path;
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(redir->file_name, line))
			break ;
		else
			ft_putendl_fd(line, file);
		count++;
		if (g_exit_status != 130 && !ft_strcmp(line, redir->file_name))
		{
			ft_free((void **)&line);
			break ;
		}
	}
}

void	ft_process_heredoc(t_redir *redir, t_data *data)
{
	char	*file_path;
	int		file;

	file = -1;
	create_filename(redir);
	if (!redir && !redir->file_here_doc)
		return ;
	file_path = redir->file_here_doc;
	file = open(file_path, O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (file == -1)
		perror("heredoc");
	signal(SIGINT, heredoc_sigint_handler);
	while (*file_path)
		file_path++;
	execute_here_doc(redir, data, file_path, file);
	close(file);
}
