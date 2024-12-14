#include "minishell.h"

static void	create_filename(t_redir *redir)
{
	char	*temp_file;
	char	*temp_num;

	temp_num = ft_itoa(getpid() + 1);
	temp_file = ft_strjoin("./minishell_heredoc_", temp_num);
	free(temp_num);
	if (!temp_file)
	{
		perror("ft_strjoin");
		free(temp_file);
		return ;
	}
	if (access(temp_file, F_OK) == -1)
	{
		redir->file_here_doc = ft_strdup(temp_file);
		free(temp_file);
		return ;
	}
	redir->file_here_doc = ft_strdup(temp_file);
	free(temp_file);
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
		if (!(var = ft_get_env_value(var, data)))
			ft_putstr_fd(var, fd);
		free(var);
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



static void	execute_here_doc(t_redir *redir, t_data *data)
{
	char	*line;
	char	*file_path;
	int		file;
	int		count;

	file = -1;
	count = 0;
	if (!redir && !redir->file_here_doc)
		return ;
	file_path = redir->file_here_doc;
	file = open(file_path, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (file == -1)
		perror("heredoc");
	signal(SIGINT, heredoc_sigint_handler);
	while (*file_path && !ft_is_quote(*file_path))
		file_path++;
	while (g_exit_status != 130)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(redir->value, line))
			break ;
		if (!*file_path)
			ft_expand_heredoc(line, file, data);
		else
			ft_putendl_fd(line, file);
		count++;
	}
	if (line)
		free(line);
	close(file);
}

void	ft_process_heredoc(t_redir *redir, t_data *data)
{
	create_filename(redir);
	execute_here_doc(redir, data);
	data->isheredoc = true;
}