/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:15:05 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 02:52:27 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_redir_value(char *str, t_envp *envp);
char	*handle_expand_variable(char *result, char *str, int *i, t_envp *envp);
char	*handle_expand_char(char *result, char c);
char	*get_env_value(const char *key, t_envp *envp);

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '-');
}

int	ft_expand_redir(char **str, t_envp *envp)
{
	char	*expanded_value;

	if (!str || !*str)
		return (ERROR);
	expanded_value = expand_redir_value(*str, envp);
	if (!expanded_value)
		return (ERROR);
	if (expanded_value[0] == '\0')
	{
		free(expanded_value);
		ft_putstr_fd("bash: ambiguous redirect\n", 2);
		return (ERROR);
	}
	ft_free((void **)str);
	*str = expanded_value;
	return (SUCCESS);
}

char	*expand_redir_value(char *str, t_envp *envp)
{
	char	*result;
	int		i;
	char	in_single;
	char	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (str[i] == '$' && !in_single && str[i + 1])
		{
			result = handle_expand_variable(result, str, &i, envp);
		}
		else
			result = handle_expand_char(result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*handle_expand_variable(char *result, char *str, int *i, t_envp *envp)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		return (free(result), NULL);
	value = get_env_value(key, envp);
	free(key);
	tmp = ft_strjoin_free(result, value, 1);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*handle_expand_char(char *result, char c)
{
	char	*tmp;
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	tmp = ft_strjoin_free(result, char_str, 1);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*get_env_value(const char *key, t_envp *envp)
{
	t_envp	*current;

	if (!key || !envp)
		return ("");
	current = envp;
	while (current)
	{
		if (!ft_strcmp(current->name, key))
			return (current->value);
		current = current->next;
	}
	return ("");
}
