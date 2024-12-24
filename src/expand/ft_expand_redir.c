/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:15:05 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/24 04:44:08 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_expand_variable(char *result, char *str, int *i, t_envp *envp);
char	*handle_expand_char(char *result, char c);
char	*get_env_value(const char *key, t_envp *envp);

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
