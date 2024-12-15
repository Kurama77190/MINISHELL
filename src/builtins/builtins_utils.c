#include "minishell.h"

void	ft_swap_env_lines(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->line;
	a->line = b->line;
	b->line = temp;
}

void	ft_sort_env(t_env *env)
{
	t_env	*tmp;
	bool	is_sort;

	is_sort = false;
	while (is_sort == false)
	{
		is_sort = true;
		tmp = env;
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->line, tmp->next->line) > 0)
			{
				ft_swap_env_lines(tmp, tmp->next);
				is_sort = false;
			}
			tmp = tmp->next;
		}
	}
}

void	copy_env(char **envp, t_data *data)
{
	int		i;
	int		len;
	char	*pwd;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	if (!len)
	{
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
		printf("No env\n");
		push_node_to_env(data, pwd);
		free(pwd);
		push_node_to_env(data, "SHLVL=0");
		push_node_to_env(data, "_=/usr/bin/env");
	}
	else
	{
		while (envp[i])
		{
			push_node_to_env(data, envp[i]);
			i++;
		}
	}
}

void	copy_env_char(t_data *data)
{
	t_env	*tmp_count;
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!data->env || !data->env->line)
		return ;
	tmp_count = data->env;
	tmp = data->env;
	while (tmp_count)
	{
		i++;
		tmp_count = tmp_count->next;
	}
	data->envc = malloc(sizeof(char *) * (i + 1));
	if (!data->envc)
	{
		ft_error(data, "error environment\n");
		return ;
	}
	i = 0;
	while (tmp)
	{
		if (tmp->line)
		{
			data->envc[i] = ft_strdup(tmp->line);
			if (!data->envc[i])
			{
				ft_error(data, "error environment\n");
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	data->envc[i] = NULL;
}
