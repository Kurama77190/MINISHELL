/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:12:35 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/17 13:06:10 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_filename(t_redir *redir)
{
	char	*temp_file;
	char	*temp_num;

	temp_num = ft_itoa(getpid() + 1);
	temp_file = ft_strjoin("./minishell_heredoc_", temp_num);
	ft_free((void**)&temp_num);
	if (!temp_file)
	{
		perror("ft_strjoin");
		ft_free((void**)&temp_file);
		return ;
	}
	if (access(temp_file, F_OK) == -1)
	{
		redir->file_name = ft_strdup(temp_file);
		ft_free((void**)&temp_file);
		return ;
	}
	redir->file_name = ft_strdup(temp_file);
	ft_free((void**)&temp_file);
}

static int	ft_env_var_heredoc(char *str, size_t i, int fd, t_data *data)
{
	size_t	start;
	char	*var;

	start = i++;
	if (str[i] == '?')
		return (ft_putnbr_fd(data->exit_status, fd), 2);
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	if (i != start)
	{
		var = ft_substr(str, start, i);
		//var = ft_get_env_value(var, data);
		if (!var)
			ft_putstr_fd("", fd);
		ft_free((void**)&var);
	}
	return (i);
}

static void	ft_expand_heredoc(char *command, int fd, t_data *data)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
			i += ft_env_var_heredoc(command, i, fd, data);
		else
			ft_putchar_fd(command[i++], fd);
	}
	ft_putchar_fd('\n', fd);
}

static void	execute_here_doc(t_redir *redir, t_data *data, char *file_path,
		int file)
{
	char	*line;
	int		count;

	count = 0;
	while (g_exit_status != 130)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(redir->file_name, line))
			break ;
		if (!*file_path)
			ft_expand_heredoc(line, file, data);
		else
			ft_putendl_fd(line, file);
		count++;
	}
	if (line)
		ft_free((void**)&line);
}

void	ft_process_heredoc(t_redir *redir, t_data *data)
{
	char	*file_path;
	int		file;

	file = -1;
	create_filename(redir);
	if (!redir && !redir->file_name)
		return ;
	file_path = redir->file_name;
	file = open(file_path, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (file == -1)
		perror("heredoc");
	signal(SIGINT, heredoc_sigint_handler);
	while (*file_path)
		file_path++;
	execute_here_doc(redir, data, file_path, file);
	close(file);
}
