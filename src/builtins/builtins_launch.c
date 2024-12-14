#include "minishell.h"

bool	ft_detect_builtin(char **argv, t_data *data)
{
	if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, data);
	else if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv, data);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(argv, data);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argv, data);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(argv, data);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv, data);
	else
		return (false);
	return (true);
}
